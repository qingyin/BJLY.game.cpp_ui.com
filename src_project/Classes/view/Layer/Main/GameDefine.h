#ifndef _GameDefine_h
#define _GameDefine_h

#include <string>
using namespace std;
#include "cocos2d.h"
using namespace cocos2d;

static const Vec2 posWait[4] = {Vec2(640.0f,150.0f),Vec2(1080.0f,360.f),Vec2(640.0f,610.0f),Vec2(200.0f,360.f)};
static const Vec2 posGame[4] = {Vec2(81.70,234.39),Vec2(1192.56,440.80),Vec2(1004.41,644.11),Vec2(85.90,442.31)};
static const Vec2 posGameluxiang[4] = {Vec2(90,142),Vec2(1179.56,397.96),Vec2(1179.01,637.48),Vec2(95.09,593.65)};

static const Vec2 posWait_three[3] = {Vec2(640.0f,150.0f),Vec2(1080.0f,360.f),Vec2(200.0f,360.f)};
static const Vec2 posGame_three[3] = {Vec2(81.70,234.39),Vec2(1192.56,440.80),Vec2(85.90,442.31)};
static const Vec2 posGameluxiang_three[3] = {Vec2(90,142),Vec2(1179.56,397.96),Vec2(95.09,593.65)};

static const Vec2 posWait_two[2] = {Vec2(640.0f,150.0f),Vec2(640.0f,610.0f)};
static const Vec2 posGame_two[2] = {Vec2(81.70,234.39),Vec2(1004.41,644.11)};
static const Vec2 posGameluxiang_two[2] = {Vec2(90,142),Vec2(1179.01,637.48)};

//���������־
enum operate_code_whx
{
	None,
	operate_peng,
	operate_zuogang,
	operate_yougang,
	operate_duimengang,
	operate_bugang,
	operate_angang,
	operate_ting,
	operate_hu,
	operate_zuopeng,
	operate_duimenpeng,
	operate_youpeng

};
//������ť��ʾ��־
enum operate_actionButtonShow
{
	None0,
	None1,
	None2,
	None3,
	operate_showpeng,
	operate_showgang,
	operate_showting,
	operate_showhu
};

//�����ͽṹ��
typedef struct hu_type_struct
{
	int viewid;
	int hutype;//
	int gangtype;
}hu_type_struct;



typedef struct operate_me
{
	int card_id;//�Ե��Ƶĵ���
	int operatecode;//�ɽ��еĲ���������ֳ� �� �� �Ȳ�����
	std::vector<int >arr_gang_mjs;//���Ըܵ�����������ʾ����

}operate_me;
typedef struct operate_result
{
	int operate_code;//�������� chi peng gang angang 
	int card_id;//�Ե��Ƶ���ֵ ��ʲô����ɵ��������
}operate_result;
typedef struct weaveitem
{
	int weavekin;//��������
	int cardid;//��ֵ
}weaveitem;
typedef struct resultitem
{
	int uid;
	std::vector<int >handcards;
	std::vector<weaveitem>arr_weaves;
	int gold_change;//Ӯ�÷���
	int hu_type;
	int gang_type;
	int jinum;
	int total_gold;
	int hu_cardid;

}resultitem;
typedef struct  oneroundresult//һ�ֽ�������
{
	std::vector<resultitem>arr_resluts;
	int fanpaiji_id;//���Ƽ�����ֵ
	int is_huangzhuang;
}oneroundresult;




typedef struct  reconnect_info
{
	std::vector<int>      hand_cards             ;               //�Լ������˿�
	std::vector<int>      hand_cnts              ;               //������ҵ������Ƹ�������    

	std::vector<  weaveitem>  weaves1            ;                //�Լ���������
	std::vector<  weaveitem>  weaves2;                //���2��������
	std::vector<  weaveitem>  weaves3;                //���3��������
	std::vector<  weaveitem>  weaves4;                //���4��������

	std::vector<int>      dismiss_cards_1         ;                //�Լ��������˿�
	std::vector<int>      dismiss_cards_2        ;                //���2�������˿�
	std::vector<int>      dismiss_cards_3        ;                //���3�������˿�
	std::vector<int>      dismiss_cards_4         ;                //���4�������˿�

	std::vector<int>      minglou_cards_1         ;                //�Լ���§���˿�
	std::vector<int>     minglou_cards_2        ;                //���2��§���˿�
	std::vector<int>     minglou_cards_3         ;                //���3��§���˿�
	std::vector<int>      minglou_cards_4        ;                //���4��§���˿�

	int      current_uid             ;               //��ǰ���
	int      left_card_cnt          ;               //ʣ������
	int      left_round             ;               //ʣ�����    

	std::vector<int>      is_minglous            ;               //����Ƿ���§����[0,1,1,1]��ʾ3�������§
	std::vector<int>      hua_cnts                ;               //��ҵĻ�������
	std::vector<int>      actions                 ;               //������ҵĶ�������   
}reconnect_info;

typedef struct  playluxiang
{
	int cardlen;
	std::vector<int >cardid;
	int actionuerid;
	int actionkind;
	int provideuserid;
}playluxiang;
typedef struct xingpai_luxiang
{
	int cardid;
	int operatecode;
}xingpai_luxiang;

#endif
