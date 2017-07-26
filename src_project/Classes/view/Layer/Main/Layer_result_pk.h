#pragma once
#include "view/ParentInfo/ParentInfo.h"
typedef struct pKlist
{
	int uid;
	std::vector<int >arr_perround_score;
}pKlist;
typedef struct arr_pklist
{
	std::vector<pKlist>arrpklist;
}arr_pklist;
class  layer_result_pk : public ParentInfo
{
public:
	void onEnter();
	void onExit();
	virtual bool init();
	void initwithdata(arr_pklist arr_p);
	void backform();
	CREATE_FUNC(layer_result_pk);
public:
	Node *n_root;
};