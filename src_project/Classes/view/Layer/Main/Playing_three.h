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
	//¼��
	void playluxiang_player(std::vector<playluxiang> arr_luxiang);

	void initplayer();//��ʼ�����

	//��Ϸ��ʼ(���ͷ��λ�ø��µ�)
	void startGame_gamePlayer(int banker, int left_card_cnt);
	//��Ϸ��ʼ������
	void addplayer(float dt);
	//����
	void dispacherCard(google::protobuf::RepeatedField< ::google::protobuf::int32 > cards);
	//�����������Ƿ��ܲ���
	void setcardoperateornot(bool is);

	//tongguourl��ȡͷ��
	void getheadpathlocalbyurl(std::string  url,int tag);
	void onGetFinished(HttpClient *sender, HttpResponse *response);
	void chushihua(bool isluxiang);
	void cleanallscene();

	void hupai_yinxiao(int op,int sex_);//���ź�����Ч
	void playeeffect_normal(std::string path);

	void addresulttotal(EventCustom* evt);
	void restarapp_main(float dt);
	void restartbyLoseConfirm(EventCustom *evt);
private:

	TipContent *tp_lose;

	void loadAndShowPlayers();
	//��ť�ص�����
	void ButtonHandler(Ref* pRef, ui::Widget::TouchEventType touchType);
	//�����ܵİ�ť�ص�
	void ButtonHandler_operate(Ref* pRef, ui::Widget::TouchEventType touchType);
	//��Ҽ�������
	void joinTable(EventCustom* evt);
	//����뿪���ӹ㲥
	void leaveTableBroadcast(EventCustom* evt);
	//��Ҳ����㲥
	void buHuaBroadcast(EventCustom* evt);
	//��ǰ���ѡ��Ҫ������(����)
	void selectCard(EventCustom* evt);
	void selectCardbylocal(MjNode *mj);
	//���ƹ㲥�����أ�
	void outCardBroadcast(EventCustom* evt);
	//��ǰ��ҳ��Ʒ��أ����������أ�
	void outCard(EventCustom* evt);

	//���������������ĳ�����Ϣ
	void outcardformserver(EventCustom *evt);
	//ϵͳ�������ƵĹ㲥
	void systemgetsiglecardbroadcast(EventCustom *evt);


	void responsegetplayerinfo(EventCustom *evt);
	//ϵͳ�㲥�û�����
	void responseoperate(EventCustom *evt);

	//��Ӧ�������
	void resultofoperate(EventCustom *evt);

	//��Ӧ��������Ĺ㲥
	void responseoperatebroadcast(EventCustom *evt);
	//��¥ѯ�ʷ���
	void responseminglouask(EventCustom *evt);
	//��¥����
	void responsemingloubroadcast(EventCustom *evt);

	//ˢ���齫λ��
	void refreshMjsPos();
	///����pMjNode �Ӵ�С
	void sortMjs(Vector<MjNode*> &_pokerVec);
	void sortMjByLaiya(std::vector<int> &arr_poker);
	void sortMjByLaiya_cardshow(std::vector<int> &arr_poker);
	void sortpokersbywhx(std::vector <MjNode *>arr_mjs);
	//ˢ�������Ƶ�λ�ã����� �Ƶ����� �Լ��Ե��ƣ�
	void refreshxingpaipos(std::vector<operate_result>arr_poker, Node *parent);
	void refreshxingpaiposofothers(std::vector<operate_result>arr_mjs,Node *parent,int viewid,int ismopai);//�Ƿ����Ŵ����� ����ˢ�� λ�ò�ͬ �Ƿ��������ط꼰
	//����������ʾ�����޸�������
	void buhuaActionManage(int uid,int numHua);
	//������ʾicon��ʾ����
	void buHuaActionEndcallback(Node* sender );
	//���Ʊ��ض���������Ļص�����
	void outCard1Action(Node* sender );

	//ˢ���ѳ��ƽ��棨4���˵�ȫ��ˢ�£�
	void refreshoutcardByViewId(int viewid);
	//ˢ�¼������
	void refreshjipaiOfPlayer(int viewid);
	//ˢ�¶�����ť����
	void refreshactionsbutton(bool iscanoperate);
	//�����������ÿɼ��Ͳ��ɼ�
	void setcards_detail_actionsisvisible(bool isvisible);

	//���ص�
	void guo_callfunc();
	//���ƻص�
	void chi_callfunc(std::vector<operate_me >arr_chi);
	//���ƻص�
	void peng_callfunc(int operatecode ,int peng_card);
	//���ƻص�
	void gang_callfunc(std::vector<operate_me>gang_arr);
	//���ƻص�
	void hu_callfunc(int actioncard);
	//��¥�ص�
	void minglou_callfunc();

	//��ʾ���ԳԵ���
	void showcards_chi(std::vector<operate_me > chi_arr);
	//��ʾ���Ըܵ���
	void showcards_gang(std::vector<operate_me>gang_arr);

	//ֱ�ӳ���
	void operate_chi(operate_me op);
	//����
	//����
	void oprate_gang(operate_me op);

	//���ճ�������
	void chi_final_request(int opcode,std::vector<int >arr_cards);

	//һ�ֽ����㲥
	void responseonroundendbroadcast(EventCustom *evt);
	//ѯ�ʽ�ɢ����
	void dismissAskBroadcast(EventCustom *evt);
	void dismisssuccessbroadcast(EventCustom *evt);
	//ready�㲥
	void responsereadybroadcast(EventCustom *evt);
	void responseready(EventCustom *evt);



	void sp_visible(Sprite *sp,bool isvisible);
	void playeraction_animation(int viewid,int operatecode);
	void playAction_hu_animation();
	void playAction_hu_animationSigile(int viewid,int hu_type);//���ŵ��������� 
	void playAction_gang_animationSigle(int viewid,int gang_type);//���ŵ����ܶ���
	void playAction_YipaoDuoxiangAnimation(std::vector<int >arr_viewids,int hu_num);//����һ�ڶ��춯��
	void playAction_jiAnimation(int viewid,int jitype);//1 ���� 2 ���μ�

	void showRresultLayerByOverAnimation(float dt);//�������ж�����Ҫ��ʾ�������
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

	//�¼ӵķ���
	void initcardWithCardIds(Sprite *cardVuleSprite,int cardValue);

	void removeSp(Sprite *sp);

	void spsetvisible(Sprite *sp,bool isvisible);

	void showfanpaiji(float dt);

	void refreshcard_show(oneroundresult r_show);//�����㲥���Ʒ���


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

	std::vector<hu_type_struct>arr_hutype;//ÿ�ν���ǰ�ĺ������Լ�������Ϣ���� �����Ŷ�����
	int operate_num;
	int hands_cnt[4];//ÿ���˵�������
	std::vector<int >arr_jipai[4];//4���˵ļ��� int ��ֵ���������� �����С����������
	Node*    nodePlayers[4];   //���Node����
	Node *   nodeCards[4];//�����˵��Ƶļ���
	Node * node_detail_actions;//�ɽ��в����İ�ť
	Node *n_action;//������ť�ĸ���
	std::vector<Button *>arr_actions;//���п��Բ����İ�ť����(�������ܹ���¥)
	std::vector<operate_me>arr_operates;//�ɽ��еĲ������飨ָ�
	bool isminglou_over;//�Ƿ���¥���

	Vector<MjNode*> m_mjList;

	bool		   mj_isSelectedMj; //�Ƿ����Ѿ�ѡ�е��齫(true:��;false:��)
	MjNode*		   mj_selectedMj;	
	MjNode *right_card_alive;//��ǰ�����ϻ���ƣ��ɳ� ���� �� �ܵ� ��Ծ���ƣ�

	std::vector<int >   m_arr_players_mjs[4];//��Ҕ��M������ѳ��Ɣ��M��
	std::vector<operate_result> m_players_chengxing_mjs[4];//����������
	bool isminglou_ing;//�Ƿ����ڽ�����¥���� ֻ��Ե�ǰ�û�
	oneroundresult r_i;//һ�ֽ�����Ϣ
	int headimage_url_loading[4];//��ǰ���ڼ��ص�ͷ��

	int m_left_card_cnt;
	Sprite*		  m_current_diamond;
	reconnect_info rr_item;//����ȫ����Ϣ	

	std::vector<playluxiang>arr_luxiang_data;
	std::vector<Node *>arr_shoupai_luxiang;
	std::vector<Node *>arr_xingpai_luxiang;
	std::vector<Node *>arr_outcard_luxiang;
	std::vector<Node *>arr_jipai_luxiang;
	std::vector<Node *>arr_node_actions;//ÿ���˵Ķ����ڵ�

	std::vector<int>arr_shoupai[4];//ÿ���˵�������

	std::vector<xingpai_luxiang>arr_xingpai[4];//ÿ���˵���������

	std::vector<int>arr_outcard[4];//ÿ���˴������

	int ji_num_players_luxiang [4];//ÿ���˵Ĵ��ȥ�ļ�������

	int right_ji_num_luxiang;//��ǰ���ȥ�ļ������� �����жϵ�ǰ�� ��漦�������μ�
	Button *bt_pause_luxiang;
	float luxiang_rate;//¼�񲥷��ٶ�

	int emoji_num[15];

	float time_all;

	//layer_result_end *layer_end;//�ܽ���
	int diamisssuccess;

	int fanpai_cardid;

	std::vector<Vec2>arr_hand_pos[4];

	MjNode *mj_outcarding;//�����϶�����

	bool isOutCarding;
	int outcardingId;
	bool iscanchupai;//�Ƿ��ܳ���

	ParticleSystem* m_emitter1;
	bool isinLuxiang;

	int dingqueshu;
};
