#pragma once
#include "DataComponent.h"
#include "GameObject.h"
class CloudDataComponent :
	public DataComponent
{
	friend class CloudGraphicsComponent;
	friend class CloudPhysicsComponent;
public:
	CloudDataComponent(__int8 Distance);

	virtual void update(GameObject&);

	~CloudDataComponent();
private:
	__int8 distance_;
};

