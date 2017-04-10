#pragma once
#include "Plane.h"

class Command
{
public:
	virtual void execute(Plane&) = 0;
};

class AccelerateCommand : public Command
{
public:
	virtual void execute(Plane& plane)
	{
		plane.acceleration_ = 3.f;
	}
};

class DecelerateCommand : public Command
{
public:
	virtual void execute(Plane& plane)
	{
		plane.acceleration_ = -3.f;
	}
};

class TurnLeftCommand : public Command
{
public:
	virtual void execute(Plane& plane)
	{
		plane.angle_ = -plane.turnSpeed_ * 1;
	}
};

class TurnRightCommand : public Command
{
public:
	virtual void execute(Plane& plane)
	{
		plane.angle_ = plane.turnSpeed_ * 1;
	}
};

class FireCommand : public Command
{
public:
	virtual void execute(Plane& plane)
	{
		//TODO
	}
};