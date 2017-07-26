#include "PageViewEx.h" 

PageViewEx::PageViewEx()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	_touchMoveDirection = TouchDirection::LEFT;
	pageViewNum = 0;
#endif
}
PageViewEx::~PageViewEx()
{
}

void PageViewEx::setPageCount(int pageNum)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	_touchMoveDirection = TouchDirection::LEFT;
	pageViewNum = pageNum;
#endif
}
int PageViewEx::getPageCount()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	return pageViewNum;
#else
	return PageView::getPageCount();
#endif
}

int PageViewEx::getScrollToIndex()
{
	int pageCount = this->getPageCount();
	int curIndex = (int)PageView::getCurPageIndex();
	log("-----PageViewEx-----pageCount=%d,curIndex=%d,direction=%d",pageCount,curIndex,_touchMoveDirection);
	if (pageCount <= 1)
	{
		return pageCount -1;
	}
	int index = -1;
	if (_touchMoveDirection == PageView::TouchDirection::LEFT)
	{
		if (curIndex ==0)
		{
			index = 1;
			_touchMoveDirection = PageView::TouchDirection::RIGHT;
		}
		else
		{
			index = curIndex - 1;
		}
	}
	else if (_touchMoveDirection == PageView::TouchDirection::RIGHT)
	{
		if (curIndex ==pageCount -1)
		{
			index = curIndex -1;
			_touchMoveDirection = PageView::TouchDirection::LEFT;
		}
		else
		{
			index = curIndex + 1;
		}
	}
	return index;
}