#pragma once
#include "view/ParentInfo/ParentInfo.h"


typedef struct result_LittleItem
{
	std::string kind_type;//ºúÅÆÀàĞÍ
	int color;
	std::string fenzhi;
	int   zhuang2bei;
}result_LittleItem;
typedef struct result_DetailItem
{
	int uid;
	std::vector<result_LittleItem>arr_littleitem;
}result_DetailItem;
typedef struct result_detail_struct
{
	std::vector<result_DetailItem>arr_detailitem;
}result_detail_struct;
class  layer_result_detail : public ParentInfo
{
public:
	void onEnter();
	void onExit();
	virtual bool init();
    void initwithdata(result_detail_struct r_d_s);
	void removesthis();
	CREATE_FUNC(layer_result_detail);
public:
	Node *n_root;
};