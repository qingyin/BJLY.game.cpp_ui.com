#pragma once
#include "view/ParentInfo/ParentInfo.h"
#include "view/Layer/Main/Playing_three.h"
#include "view/Layer/Main/Layer_result3.h"
#include "view/Layer/Main/layer_result1.h"
typedef struct hu_type
{
	int uid;
	int hutype;
	int gang_type;
	int fenzhi_win;
}hu_type;
class  layer_result : public ParentInfo
{
public:
	void onEnter();
	void onExit();
	virtual bool init();
	void initwithdata(oneroundresult one_re);
	void clickbt_share();
	void clickbt_next();
	void clickbt_detail();
	void initwithdissmiss();
	void initcardWithCardIds(Sprite *cardVuleSprite,int cardValue);

	void sortMjByLaiya(std::vector<int> &arr_poker);
	
	void addresultdetail(EventCustom* evt);
	void readyForRemoveSelf(EventCustom *evt);
	void showresultpk();

	CREATE_FUNC(layer_result);
public:
	Sprite *sp_win_tag;//ƒ„”Æ¡À ƒ„ ‰¡À ª∆◊Ø
	//Text *tx_rule;
	Text *tx_room_id;
	Button *bt_share;
	Button *bt_next;
	Button *bt_detail;
	std::vector<Node *>arr_n_players;
	Sprite *sp_ishuang;
	Sprite *sp_mj_value;
	int uid[4];
	int win_tag;// ‰”Æ 1”Æ 2 ‰ 3∆Ω
	std::vector<hu_type>arr_hu;

	layer_result_detail *l_detail;
};
