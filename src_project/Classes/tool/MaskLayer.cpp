#include "MaskLayer.h"

MaskLayer* MaskLayer::createMaskLayer(int width, int height, int opacity){
	MaskLayer* layer = new MaskLayer;
	if (layer && layer->init(width,height,opacity))
	{
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return nullptr;
}

bool MaskLayer::init(int width, int height, int opacity){
	if (!LayerColor::init())
	{
		return false;
	}
	this->setContentSize(Size(width, height));
	this->initWithColor(Color4B(0, 0, 0, 200));
	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->onTouchBegan = CC_CALLBACK_2(MaskLayer::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
	return true;
}

bool MaskLayer::onTouchBegan(Touch *touch, Event *unused_event){
	unused_event->stopPropagation();
	return false;
}
