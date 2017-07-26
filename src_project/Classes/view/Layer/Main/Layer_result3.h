#pragma once
#include "view/ParentInfo/ParentInfo.h"
typedef struct result_total
{
	int total_uid;
	int total_fen;
	std::vector<int >arr_fen_perround;
}result_total;
typedef struct result_total_all
{
	std::vector<result_total >arr_total_all;
}result_total_all;
class  layer_result_end : public ParentInfo
{
public:
	void onEnter();
	void onExit();
	virtual bool init();
	void initwithdata(result_total_all a);
	void backform();
	void sharewinxin();
	CREATE_FUNC(layer_result_end);
public:
	Node *n_root;
};