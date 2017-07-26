//
//  GameConst.h


#ifndef _GameConst_h
#define _GameConst_h

#include <string>
using namespace std;

namespace GameConst
{
	static const string key_activity_num = "key_activity_num";
	static const string key_activity_id_ = "key_activity_id_";
	static const string key_event_activity = "key_event_activity";
	static const string key_activity_pic_url_ = "key_activity_pic_url_";

	static const string key_wx_base_service_ = "key_wx_base_service_";
	static const string key_wx_base_agent_ = "key_wx_base_agent_";
	static const string key_wx_base_buy_ = "key_wx_base_buy_";
	static const string key_wx_base_feedback = "key_wx_base_feedback";
	static const string key_remove_lobby = "key_remove_lobby";

	static const string key_speaker_content = "speakerContent";

	static const string key_myInviteCode = "key_myInviteCode";//我的邀请码
	static const string key_myPromoterID = "key_myPromoterID";//我的推广员ID
	static const string key_RefereeCode = "key_RefereeCode";//推荐人邀请码


	//const std::string URL = "http://120.77.175.70:56492/";
	//const std::string URL = "http://192.168.1.164:56492/";
	//const std::string URL = "http://119.23.255.124:56492/";
	//static  std::string URL = "http://182.92.161.204:56492/";//bate
	
	static std::string URL = "http://apijp.laiyagame.com:56492/";
	static std::string URL_version_verify = "http://apijp.laiyagame.cn:56492/";
};

namespace CustomEvent
{
	static const string key_show_ui_message = "key_show_ui_message";
	static const string key_show_ui_activity = "key_show_ui_activity";
	static const string key_show_ui_self_info = "key_show_ui_self_info";
	static const string key_show_ui_record = "key_show_ui_record";
	static const string key_show_ui_bind_confirm = "key_show_ui_bind_confirm";
	static const string key_update_ui_bind = "key_update_ui_bind";
	static const string key_show_laba = "key_show_laba";
	static const string key_update_self_info = "key_update_self_info";
	static const string key_set_visible_loading_layer = "key_set_visible_loading_layer";
	static const string key_show_game_main = "key_show_game_main";
	static const string key_show_low_net_layer = "key_show_low_net_layer";
	static const string key_show_game_menu = "key_show_game_menu";
	static const string key_show_request_headinfo = "key_show_request_headinfo";
	static const string key_show_update_head = "key_show_update_head";	
	static const string key_version_verify = "key_version_verify";	
};

namespace RequestUrl
{
	static const string GET_ACTIVITY_PICLIST = "/getActivityPicList";
	static const string GET_PARTNER_INFO = "/getPartnerInfo";
	static const string GETP_LAYER_INFO_BY_INVITE_CODE = "/getPlayerInfoByInviteCode";
	static const string BIND_PLAYER = "/bindPlayer";
	static const string BIND_PARTNER = "/bindPartner";
	static const string GET_PLAYER_MESSAGE = "/getPlayerMessage";
	static const string GET_CONTACT_INFO = "/getContactInfo";

	static const string GET_HISTORY = "/get_history";
	static const string GET_JU_CNT = "/get_ju_cnt";
	static const string TEST_READ_TIMEOUT = "/test_read_timeout";
	static const string  WEICHAT_LOGIN = "/weichat_login";
	static const string  VERSION_VERIFY = "/version_verify";	
};

namespace MsgData
{
	namespace ContactInfo
	{
		static const string buyCard1 = "buyCard1";
		static const string buyCard2 = "buyCard2";
		static const string feedback = "feedback";
		static const string joinAgent1 = "joinAgent1";
		static const string joinAgent2 = "joinAgent2";
		static const string support1 = "support1";
		static const string support2 = "support2";
	};
};

#endif
