#include "Tiperror.h"
#include "Tools.h"

bool Tiplayerr::init(string game_msg)
{
	if(!ParentInfo::init())return false;
	setDelete(true);
	m_root = CSLoader::createNode("res/loading/Tiperror.csb");
	addChild(m_root);

	auto tipTxt = (Text*)m_root->getChildByName("Text_error");
	tipTxt->setString(game_msg);

	return true;
}
void Tiplayerr::onExit()
{
	ParentInfo::onExit();
}
