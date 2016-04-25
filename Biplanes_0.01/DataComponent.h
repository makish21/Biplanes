#pragma once
#include "GameObject.h"

class DataComponent
{
public:
	virtual void update(GameObject&) = 0;
	~DataComponent() {}
};