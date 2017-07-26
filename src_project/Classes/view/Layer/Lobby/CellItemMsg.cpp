#include "CellItemMsg.h"

#include "tool/Tools.h"
#include "tool/Convert.h"
bool CellItemMsg::init()
{
	if (!ParentInfo::init())
	{
		return false;
	}
	setSwallowTouches(false);

	ccColor4B color(0,0,0,0);  //设置面板颜色及透明度
	LayerColor::initWithColor(color);

	auto root_node = CSLoader::createNode("res/loading/lobbyCsd/CellItemMsg.csb");
	this->addChild(root_node);
	txt_dateTime = (Text*)root_node->getChildByName("txt_dateTime");
	txt_msgContent = (Text*)root_node->getChildByName("txt_msgContent");
	txt_msgTitle = (Text*)root_node->getChildByName("txt_msgTitle");
	//((Button*)root_node->getChildByName("btn_review"))->addClickEventListener(CC_CALLBACK_1(CellItemMsg::BtnEvent,this));
	return true;
}

void CellItemMsg::setData(int id,string dateTime,string msgContent,string msgTitle)
{
	this->id = id;
	//this->txt_msgContent->setString(Tools::StrToUTF8(msgContent));
	this->txt_msgContent->setString(msgContent);
	//this->txt_msgContent->setString(utility::a_u8(msg));
	this->txt_dateTime->setString(dateTime);
	//this->txt_msgTitle->setString(Tools::StrToUTF8(msgTitle));
	this->txt_msgTitle->setString(msgTitle);
	//txt_dateTime->setFocusEnabled()
}

void CellItemMsg::BtnEvent(Ref* sender)
{
	log("----CellItemRecord----%d",this->id);
}