#pragma once
#include "InputComponent.h"
#include "GameObject.h"
class EmptyInputComponent :
	public InputComponent
{
public:
	EmptyInputComponent();

	virtual void update(GameObject&);

	~EmptyInputComponent();
};

