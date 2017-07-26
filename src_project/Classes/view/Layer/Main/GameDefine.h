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

//操作结果标志
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
//操作按钮显示标志
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

//胡类型结构体
typedef struct hu_type_struct
{
	int viewid;
	int hutype;//
	int gangtype;
}hu_type_struct;



typedef struct operate_me
{
	int card_id;//吃的牌的点数
	int operatecode;//可进行的操作（左吃又吃 碰 杠 等操作）
	std::vector<int >arr_gang_mjs;//可以杠的数组用于提示操作

}operate_me;
typedef struct operate_result
{
	int operate_code;//成型类型 chi peng gang angang 
	int card_id;//吃的牌的数值 吃什么牌组成的这个牌型
}operate_result;
typedef struct weaveitem
{
	int weavekin;//行牌类型
	int cardid;//牌值
}weaveitem;
typedef struct resultitem
{
	int uid;
	std::vector<int >handcards;
	std::vector<weaveitem>arr_weaves;
	int gold_change;//赢得番薯
	int hu_type;
	int gang_type;
	int jinum;
	int total_gold;
	int hu_cardid;

}resultitem;
typedef struct  oneroundresult//一局结束数据
{
	std::vector<resultitem>arr_resluts;
	int fanpaiji_id;//翻牌鸡的牌值
	int is_huangzhuang;
}oneroundresult;




typedef struct  reconnect_info
{
	std::vector<int>      hand_cards             ;               //自己手中扑克
	std::vector<int>      hand_cnts              ;               //所有玩家的手中牌个数数组    

	std::vector<  weaveitem>  weaves1            ;                //自己套牌数组
	std::vector<  weaveitem>  weaves2;                //玩家2套牌数组
	std::vector<  weaveitem>  weaves3;                //玩家3套牌数组
	std::vector<  weaveitem>  weaves4;                //玩家4套牌数组

	std::vector<int>      dismiss_cards_1         ;                //自己丢弃的扑克
	std::vector<int>      dismiss_cards_2        ;                //玩家2丢弃的扑克
	std::vector<int>      dismiss_cards_3        ;                //玩家3丢弃的扑克
	std::vector<int>      dismiss_cards_4         ;                //玩家4丢弃的扑克

	std::vector<int>      minglou_cards_1         ;                //自己明搂的扑克
	std::vector<int>     minglou_cards_2        ;                //玩家2明搂的扑克
	std::vector<int>     minglou_cards_3         ;                //玩家3明搂的扑克
	std::vector<int>      minglou_cards_4        ;                //玩家4明搂的扑克

	int      current_uid             ;               //当前玩家
	int      left_card_cnt          ;               //剩余张数
	int      left_round             ;               //剩余局数    

	std::vector<int>      is_minglous            ;               //玩家是否明搂数组[0,1,1,1]表示3个玩家明搂
	std::vector<int>      hua_cnts                ;               //玩家的花数数组
	std::vector<int>      actions                 ;               //断线玩家的动作数组   
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
