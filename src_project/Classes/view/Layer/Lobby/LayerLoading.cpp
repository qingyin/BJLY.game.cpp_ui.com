#include "LayerLoading.h"


LayerLoading::LayerLoading(void)
{
}


LayerLoading::~LayerLoading(void)
{
}
bool LayerLoading::init()
{
	if(!ParentInfo::init()) return false;
	auto root_node = CSLoader::createNode("res/loading/lobbyCsd/LayerLoading.csb");
	this->addChild(root_node);
	this->setName("LayerLoading");

	Sprite* icon_loading = (Sprite*)root_node->getChildByName("icon_loading");
	CCRotateBy* rotate = CCRotateBy::create(2,360);
	icon_loading->runAction(RepeatForever::create(rotate));
	return true;
}
