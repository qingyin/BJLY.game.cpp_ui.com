#pragma once


#include "view/ParentInfo/ParentInfo.h"

class LayerLoading : public ParentInfo
{
public:
	virtual bool init(); 
	CREATE_FUNC(LayerLoading);
	LayerLoading(void);
	~LayerLoading(void);
};

