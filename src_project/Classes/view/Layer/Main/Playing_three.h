#pragma once
#include "MjNode.h"
#include "view/ParentInfo/ParentInfo.h"
#include "controller/table/TableCommand.h"
#include "net/Http.h"
#include "view/Layer/Main/Layer_result3.h"
#include "view/Layer/Tip/TipContent.h"
#include "view/Layer/Main/GameDefine.h"
#include "view/Layer/Main/Playing_parent.h"
class Playing_three : public Playing_parent
{
public:
	void onEnter();
	void onExit();
	void refreshhead();
	virtual bool init();
	CREATE_FUNC(Playing_three);
	virtual bool onTouchBegan(Touch* touch, Event  *event) ;  
	virtual void onTouchMoved(Touch* touch, Event  *event) ;  
	virtual void onTouchEnded(Touch* touch, Event  *event) ;  

public:
	//录像
	void playluxiang_player(std::vector<playluxiang> arr_luxiang);

	void initplayer();//初始化玩家

	//游戏开始(玩家头像位置更新等)
	void startGame_gamePlayer(int banker, int left_card_cnt);
	//游戏开始添加玩家
	void addplayer(float dt);
	//发牌
	void dispacherCard(google::protobuf::RepeatedField< ::google::protobuf::int32 > cards);
	//设置手中牌是否能操作
	void setcardoperateornot(bool is);

	//tongguourl获取头像
	void getheadpathlocalbyurl(std::string  url,int tag);
	void onGetFinished(HttpClient *sender, HttpResponse *response);
	void chushihua(bool isluxiang);
	void cleanallscene();

	void hupai_yinxiao(int op,int sex_);//播放胡牌音效
	void playeeffect_normal(std::string path);

	void addresulttotal(EventCustom* evt);
	void restarapp_main(float dt);
	void restartbyLoseConfirm(EventCustom *evt);
private:

	TipContent *tp_lose;

	void loadAndShowPlayers();
	//按钮回调函数
	void ButtonHandler(Ref* pRef, ui::Widget::TouchEventType touchType);
	//吃碰杠的按钮回调
	void ButtonHandler_operate(Ref* pRef, ui::Widget::TouchEventType touchType);
	//玩家加入桌子
	void joinTable(EventCustom* evt);
	//玩家离开桌子广播
	void leaveTableBroadcast(EventCustom* evt);
	//玩家补花广播
	void buHuaBroadcast(EventCustom* evt);
	//当前玩家选中要出的牌(本地)
	void selectCard(EventCustom* evt);
	void selectCardbylocal(MjNode *mj);
	//出牌广播（本地）
	void outCardBroadcast(EventCustom* evt);
	//当前玩家出牌返回（服务器返回）
	void outCard(EventCustom* evt);

	//服务器返回真正的出牌信息
	void outcardformserver(EventCustom *evt);
	//系统发单张牌的广播
	void systemgetsiglecardbroadcast(EventCustom *evt);


	void responsegetplayerinfo(EventCustom *evt);
	//系统广播用户操作
	void responseoperate(EventCustom *evt);

	//响应操作结果
	void resultofoperate(EventCustom *evt);

	//响应操作结果的广播
	void responseoperatebroadcast(EventCustom *evt);
	//明楼询问返回
	void responseminglouask(EventCustom *evt);
	//明楼返回
	void responsemingloubroadcast(EventCustom *evt);

	//刷新麻将位置
	void refreshMjsPos();
	///排列pMjNode 从大到小
	void sortMjs(Vector<MjNode*> &_pokerVec);
	void sortMjByLaiya(std::vector<int> &arr_poker);
	void sortMjByLaiya_cardshow(std::vector<int> &arr_poker);
	void sortpokersbywhx(std::vector <MjNode *>arr_mjs);
	//刷新手中牌的位置（根据 牌的数量 以及吃的牌）
	void refreshxingpaipos(std::vector<operate_result>arr_poker, Node *parent);
	void refreshxingpaiposofothers(std::vector<operate_result>arr_mjs,Node *parent,int viewid,int ismopai);//是否摸排代表着 手牌刷新 位置不同 是否是碰的重逢及
	//补花动画显示并且修改其数量
	void buhuaActionManage(int uid,int numHua);
	//补花提示icon显示结束
	void buHuaActionEndcallback(Node* sender );
	//出牌本地动画结束后的回调函数
	void outCard1Action(Node* sender );

	//刷新已出牌界面（4個人的全部刷新）
	void refreshoutcardByViewId(int viewid);
	//刷新鸡排组合
	void refreshjipaiOfPlayer(int viewid);
	//刷新动作按钮集合
	void refreshactionsbutton(bool iscanoperate);
	//操作牌型设置可见和不可见
	void setcards_detail_actionsisvisible(bool isvisible);

	//过回调
	void guo_callfunc();
	//吃牌回调
	void chi_callfunc(std::vector<operate_me >arr_chi);
	//碰牌回调
	void peng_callfunc(int operatecode ,int peng_card);
	//杠牌回调
	void gang_callfunc(std::vector<operate_me>gang_arr);
	//胡牌回调
	void hu_callfunc(int actioncard);
	//明楼回调
	void minglou_callfunc();

	//显示可以吃的牌
	void showcards_chi(std::vector<operate_me > chi_arr);
	//显示可以杠的牌
	void showcards_gang(std::vector<operate_me>gang_arr);

	//直接吃牌
	void operate_chi(operate_me op);
	//杠牌
	//杠牌
	void oprate_gang(operate_me op);

	//最终吃牌请求
	void chi_final_request(int opcode,std::vector<int >arr_cards);

	//一局结束广播
	void responseonroundendbroadcast(EventCustom *evt);
	//询问解散房间
	void dismissAskBroadcast(EventCustom *evt);
	void dismisssuccessbroadcast(EventCustom *evt);
	//ready广播
	void responsereadybroadcast(EventCustom *evt);
	void responseready(EventCustom *evt);



	void sp_visible(Sprite *sp,bool isvisible);
	void playeraction_animation(int viewid,int operatecode);
	void playAction_hu_animation();
	void playAction_hu_animationSigile(int viewid,int hu_type);//播放单个胡动画 
	void playAction_gang_animationSigle(int viewid,int gang_type);//播放单个杠动画
	void playAction_YipaoDuoxiangAnimation(std::vector<int >arr_viewids,int hu_num);//播放一炮多响动画
	void playAction_jiAnimation(int viewid,int jitype);//1 冲锋机 2 责任及

	void showRresultLayerByOverAnimation(float dt);//放完所有动画后要显示结果界面
	void responsebreakbackbroadcast(EventCustom *evt);	


	void responsereconnect(EventCustom *evt);
	void responsepalyeffect(EventCustom *evt);

	void updateactions(float dt);



	void dispathercardsfromluxing(playluxiang p);

	void chupaifomluxiang(playluxiang p);

	void refreshshoupaifromluxiang(int viewid);
	int getlogicvalue(int a);

	void refreshchupaifromluxiang(int viewid);

	void mopaifromluxiang(playluxiang p);

	void buhuafromluxiang(playluxiang p);

	void leftchifromluxiang(playluxiang p);
	void refreshxingpaifromluxiang(int viewid);

	void minggangfromluxiang(playluxiang p);
	void angangfromluxiang(playluxiang p);

	void refreshminglou(int viewid);

	void mingloufromluxiang(playluxiang p);

	void hufromluxiang(playluxiang p);
	void refreshjipaifromluxiang(int viewid);

	void nextstep(float dt);

	void refreshzhishifromluxiang(int viewid);

	void nextfromluxiang();
	void beforefromluxiang();
	void pausefromluxiang();


	void removeluxiang();

	void playEffectCustom(std::string kName,int viewid);
	void on_effect_over(int viewid);


	void resposneplayeffect();


	void responsechatbroadcast(EventCustom *evt);
	void responsecustomchatbroadcast(EventCustom *evt);	
	void recoverchat(int viewid,Sprite *sp);
	void responsebreakbroadcast(EventCustom *evt);
	void showresult3(EventCustom *evt);

	void minglououtcarddelay(float dt);


	void losconnect(EventCustom *evt);

	//新加的方法
	void initcardWithCardIds(Sprite *cardVuleSprite,int cardValue);

	void removeSp(Sprite *sp);

	void spsetvisible(Sprite *sp,bool isvisible);

	void showfanpaiji(float dt);

	void refreshcard_show(oneroundresult r_show);//结束广播亮牌方法


	void responsepkbroadcast(EventCustom *evt);
	void responseshowpk(EventCustom *evt);

	void recovercupai(float dt);

	void spsettexture(Sprite *sp,std::string path);


	void delayShowCurrentDiamond(float dt);


	void responseaskdingquebroadcast(EventCustom *evt);
	//void responsedingqueanser(EventCustom *evt);
	void responseanserBroadcast(EventCustom *evt);
	void clickdingquecallback(int ding_num);
	void mydingquesuccess(EventCustom *evt);
	void refreshdingque(int dingdeque,int viewid);
	void refreshcolor();
private:

	std::vector<hu_type_struct>arr_hutype;//每次结算前的胡牌者以及胡牌信息集合 用来放动画的
	int operate_num;
	int hands_cnt[4];//每个人的手牌数
	std::vector<int >arr_jipai[4];//4个人的鸡排 int 数值代表鸡的类型 数组大小代表鸡的数量
	Node*    nodePlayers[4];   //玩家Node集合
	Node *   nodeCards[4];//所有人的牌的集合
	Node * node_detail_actions;//可进行操作的按钮
	Node *n_action;//造作按钮的弗雷
	std::vector<Button *>arr_actions;//所有可以操作的按钮集合(胡听碰杠过明楼)
	std::vector<operate_me>arr_operates;//可进行的操作数组（指令）
	bool isminglou_over;//是否明楼完毕

	Vector<MjNode*> m_mjList;

	bool		   mj_isSelectedMj; //是否有已经选中的麻将(true:是;false:否)
	MjNode*		   mj_selectedMj;	
	MjNode *right_card_alive;//当前牌桌上活动的牌（可吃 可碰 可 杠的 活跃的牌）

	std::vector<int >   m_arr_players_mjs[4];//玩家數組【玩家已出牌數組】
	std::vector<operate_result> m_players_chengxing_mjs[4];//成型牌数组
	bool isminglou_ing;//是否正在进行名楼操作 只针对当前用户
	oneroundresult r_i;//一局结束信息
	int headimage_url_loading[4];//当前正在加载的头像

	int m_left_card_cnt;
	Sprite*		  m_current_diamond;
	reconnect_info rr_item;//重连全部信息	

	std::vector<playluxiang>arr_luxiang_data;
	std::vector<Node *>arr_shoupai_luxiang;
	std::vector<Node *>arr_xingpai_luxiang;
	std::vector<Node *>arr_outcard_luxiang;
	std::vector<Node *>arr_jipai_luxiang;
	std::vector<Node *>arr_node_actions;//每个人的动作节点

	std::vector<int>arr_shoupai[4];//每个人的手中牌

	std::vector<xingpai_luxiang>arr_xingpai[4];//每个人的行牌数组

	std::vector<int>arr_outcard[4];//每个人打出的牌

	int ji_num_players_luxiang [4];//每个人的打出去的鸡牌数量

	int right_ji_num_luxiang;//当前打出去的鸡的总数 用来判断当前是 冲锋鸡还是责任鸡
	Button *bt_pause_luxiang;
	float luxiang_rate;//录像播放速度

	int emoji_num[15];

	float time_all;

	//layer_result_end *layer_end;//总结算
	int diamisssuccess;

	int fanpai_cardid;

	std::vector<Vec2>arr_hand_pos[4];

	MjNode *mj_outcarding;//正在拖动的牌

	bool isOutCarding;
	int outcardingId;
	bool iscanchupai;//是否能出牌

	ParticleSystem* m_emitter1;
	bool isinLuxiang;

	int dingqueshu;
};
