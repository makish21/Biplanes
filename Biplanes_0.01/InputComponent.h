#pragma once

#include "GameObject.h"

class InputComponent
{
public:
	virtual void update(GameObject&) = 0;
	~InputComponent() {}
};

