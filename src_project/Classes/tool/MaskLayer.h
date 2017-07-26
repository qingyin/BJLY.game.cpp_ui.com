
#include "cocos2d.h"
using namespace cocos2d;
class MaskLayer :public LayerColor
{
public:
	static MaskLayer* createMaskLayer(int width, int height, int opacity);
	bool init(int width, int height, int opacity);
	bool onTouchBegan(Touch *touch, Event *unused_event);

};

