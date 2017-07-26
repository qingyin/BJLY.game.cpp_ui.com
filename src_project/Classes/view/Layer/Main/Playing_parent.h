#pragma once
#include "MjNode.h"
#include "view/ParentInfo/ParentInfo.h"
#include "controller/table/TableCommand.h"
#include "net/Http.h"
#include "view/Layer/Main/Layer_result3.h"
#include "view/Layer/Tip/TipContent.h"
#include "view/Layer/Main/GameDefine.h"
class Playing_parent : public Layer
{
public:
	
	virtual void startGame_gamePlayer(int banker, int left_card_cnt){};
    virtual void chushihua(bool isLuxiang){};
	virtual void dispacherCard(google::protobuf::RepeatedField< ::google::protobuf::int32 > cards){};
	
	virtual void setcardoperateornot(bool is){};
	virtual void playluxiang_player(std::vector<playluxiang> arr_luxiang){};

};
