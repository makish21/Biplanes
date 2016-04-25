#include "CloudDataComponent.h"


CloudDataComponent::CloudDataComponent(__int8 Distance)
{
	distance_ = Distance;
}

void CloudDataComponent::update(GameObject& cloud)
{
	cloud.layer_ = 5 - distance_;
}

CloudDataComponent::~CloudDataComponent()
{
}
