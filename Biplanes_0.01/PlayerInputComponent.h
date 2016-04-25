#pragma once
#include "InputComponent.h"
#include "PlayerDataComponent.h"

#define KP sf::Keyboard::isKeyPressed

class PlayerInputComponent :
	public InputComponent
{
public:
	PlayerInputComponent();
	PlayerInputComponent(PlayerDataComponent*);

	virtual void update(GameObject&);

	~PlayerInputComponent();
private:
	void acceleration();
	void deceleration();
	void rotationLeft();
	void rotationRight();
	void fire();

	PlayerDataComponent* data_;
};

