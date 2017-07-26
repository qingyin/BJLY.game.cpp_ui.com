#include "CellItemRecord.h"

#include "tool/Tools.h"
#include "tool/Convert.h"
bool CellItemRecord::init()
{
	if (!ParentInfo::init())
	{
		return false;
	}
	setSwallowTouches(false);

	ccColor4B color(0,0,0,0);  //设置面板颜色及透明度
	LayerColor::initWithColor(color);

	auto root_node = CSLoader::createNode("res/loading/lobbyCsd/CellItemRecord.csb");
	this->addChild(root_node);
	roomCode = (Text*)root_node->getChildByName("txt_roomCode");
	dateTime = (Text*)root_node->getChildByName("txt_dateTime");
	for (int i=0;i<4;i++)
	{
		playNameScore[i] = (Text*)root_node->getChildByName(StringUtils::format("txt_player%d",i+1));
	}
	((Button*)root_node->getChildByName("btn_review"))->addClickEventListener(CC_CALLBACK_1(CellItemRecord::BtnEvent,this));
	return true;
}

void CellItemRecord::setData(string roomCode,string dateTime,string play1NameScore,string play2NameScore,string play3NameScore,string play4NameScore,int indexID)
{
	this->roomCode->setString(roomCode);
	this->dateTime->setString(dateTime);
	playNameScore[0]->setString(Tools::StrToUTF8(play1NameScore));
	playNameScore[1]->setString(Tools::StrToUTF8(play2NameScore));
	playNameScore[2]->setString(Tools::StrToUTF8(play3NameScore));
	playNameScore[3]->setString(Tools::StrToUTF8(play4NameScore));
	this->indexID = indexID;
}

void CellItemRecord::BtnEvent(Ref* sender)
{
	CCLOG("----CellItemRecord----%d",this->indexID);
}