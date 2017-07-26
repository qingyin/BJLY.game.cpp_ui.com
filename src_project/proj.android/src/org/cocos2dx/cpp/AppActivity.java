/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
 ****************************************************************************/
package org.cocos2dx.cpp;

import java.io.File;
import java.io.IOException;
import java.util.List;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import android.annotation.SuppressLint;
import android.annotation.TargetApi;
import android.app.ActivityManager;
import android.app.ActivityManager.RunningTaskInfo;
import android.app.Service;
import android.content.BroadcastReceiver;
import android.content.ClipData;
import android.content.ClipboardManager;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.pm.PackageInfo;
import android.media.MediaRecorder;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.Build;
import android.os.Bundle;
import android.os.Vibrator;
import android.util.AndroidException;
import android.util.Log;
import android.view.WindowManager;

@SuppressLint("InlinedApi") public class AppActivity extends Cocos2dxActivity {
	public static AppActivity appThis;

	

	// 褰曢煶绫�
	private MediaRecorder mediaRecorder;
	// 浠ユ枃浠剁殑褰㈠紡淇濆瓨
	private File recordFile;
	
	private BroadcastReceiver netstatereceiver;
	private BroadcastReceiver bettrystatereceiver;
	
	private static boolean isRuningTopState = false;
	private static boolean myHasFocus = false;
	private static int stateConn = 0;
	private static int leve_baterry = 50;
	private static int scale_baterry = 100;
    //剪切板管理工具类
    private static ClipboardManager mClipboardManager;
    //剪切板Data对象
    private static ClipData mClipData;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
		mClipboardManager = (ClipboardManager) getSystemService(CLIPBOARD_SERVICE);
		
		recordFile = new File("/mnt/sdcard", "kk.wav");
		appThis = this;
		Log.d("kaishi", "kaishi");
		isRuningTopState = true;
		myHasFocus = true;
		IntentFilter netstatefilter = new IntentFilter(
				ConnectivityManager.CONNECTIVITY_ACTION);
		netstatereceiver = new BroadcastReceiver() {
			@Override
			public void onReceive(Context context, Intent intent) {
				ConnectivityManager manager = (ConnectivityManager) getSystemService(Context.CONNECTIVITY_SERVICE);
				manager.getActiveNetworkInfo();
				boolean etherconn = false;
				boolean wificonn = false;
				boolean mobileconn = false;
				try {
					NetworkInfo etherinfo = manager
							.getNetworkInfo(ConnectivityManager.TYPE_ETHERNET);
					if (etherinfo.getState() == NetworkInfo.State.CONNECTED)
						etherconn = true;
				} catch (Exception e) {
				}
				try {
					NetworkInfo wifiinfo = manager
							.getNetworkInfo(ConnectivityManager.TYPE_WIFI);
					if (wifiinfo.getState() == NetworkInfo.State.CONNECTED)
						wificonn = true;
				} catch (Exception e) {
				}
				try {
					NetworkInfo mobileinfo = manager
							.getNetworkInfo(ConnectivityManager.TYPE_MOBILE);
					if (mobileinfo.getState() == NetworkInfo.State.CONNECTED)
						mobileconn = true;
				} catch (Exception e) {
				}

				int state = 0;
				if (etherconn)
					state = 1;
				else if (wificonn)
					state = 2;
				else if (mobileconn)
					state = 3;
				stateConn = state;
				
				appThis.runOnGLThread(new Runnable() {
                     @Override
                     public void run() {
                    	 Native.setNetworkState(stateConn);
                     }
                 });
				//Native.setNetworkState(state);
			}
		};
		registerReceiver(netstatereceiver, netstatefilter);
		
		
		
		
		IntentFilter intentFilter = new IntentFilter(
				Intent.ACTION_BATTERY_CHANGED);
		bettrystatereceiver = new BroadcastReceiver(){
			@Override
			public void onReceive(Context context, Intent intent) {
				if(Intent.ACTION_BATTERY_CHANGED.equals(intent.getAction())){
					//获取当前电量
					leve_baterry = intent.getIntExtra("level", 0);
					//电量的总刻度
					scale_baterry = intent.getIntExtra("scale", 100);
				}
				appThis.runOnGLThread(new Runnable() {
                     @Override
                     public void run() {
                    	
                    	 Native.setBatteryState(leve_baterry);
                     }
                 });
				
			}
		};
		registerReceiver(bettrystatereceiver, intentFilter);
	}
	
	@Override
	protected void onResume() {
		super.onResume();
		
	}
	@Override
	protected void onPause() {
		super.onPause();
		isRuningTopState = false;
	}

	@Override
	protected void onDestroy() {
		super.onDestroy();
		isRuningTopState = false;
	}
	@Override
	protected void onStop() {
		super.onStop();
		isRuningTopState = false;
	}
	public static void restartApp() {
		appThis.restart();
		
	}

	public void restart() {
    	unregisterReceiver(netstatereceiver);
		finish();
		Intent i = getBaseContext().getPackageManager()
				.getLaunchIntentForPackage(getBaseContext().getPackageName());
		i.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
		//i.addFlags(Intent.FLAG_ACTIVITY_SINGLE_TOP);
		startActivity(i);
		android.os.Process.killProcess(android.os.Process.myPid());
	}

	public static void Vibrate() {
		Vibrator vib = (Vibrator) appThis
				.getSystemService(Service.VIBRATOR_SERVICE);
		vib.vibrate(800);
	}

	// 寮�濮嬪綍闊�
	public static void startRecording() {
		appThis.mediaRecorder = new MediaRecorder();
		// 鍒ゆ柇锛岃嫢褰撳墠鏂囦欢宸插瓨鍦紝鍒欏垹闄�
		if (appThis.recordFile.exists()) {
			appThis.recordFile.delete();
		}
		appThis.mediaRecorder.setAudioSource(MediaRecorder.AudioSource.MIC);
		appThis.mediaRecorder
				.setOutputFormat(MediaRecorder.OutputFormat.AAC_ADTS);
		appThis.mediaRecorder.setAudioEncoder(MediaRecorder.AudioEncoder.AAC);
		appThis.mediaRecorder.setOutputFile(appThis.recordFile
				.getAbsolutePath());

		try {
			// 鍑嗗濂藉紑濮嬪綍闊�
			appThis.mediaRecorder.prepare();

			appThis.mediaRecorder.start();
		} catch (IllegalStateException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	// 鍋滄褰曢煶
	public static void stopRecording() {
		if (appThis.recordFile != null) {
			appThis.mediaRecorder.stop();
			appThis.mediaRecorder.release();
		}
	}
	/*
	 * //褰曢煶鎾斁 private void playRecording() { player.playRecordFile(recordFile);
	 * }
	 */
	public static boolean isTopActivy()
    {  		
		return true;
    } 
    @Override
    public void onWindowFocusChanged(boolean hasFocus) {
        super.onWindowFocusChanged(hasFocus);        
        this.myHasFocus = hasFocus;        
    }
	 public static boolean CopyText(String copyTxt)
	{
        //创建一个新的文本clip对象
        mClipData = ClipData.newPlainText("Simple test", copyTxt);
        //把clip对象放在剪贴板中
        mClipboardManager.setPrimaryClip(mClipData);
        return true;
	 }
	public static String getAppVersion() throws AndroidException
	{
		PackageInfo pInfo = getContext().getPackageManager().getPackageInfo(getContext().getPackageName(), 0);
		String version = pInfo.versionName;// +" "+ pInfo.versionCode;	
		Log.d("version==============",version);
		return version;
	}
}
