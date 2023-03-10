#pragma once
#include "Aircraft.hpp"
#include "InputCommandQueue.h"

struct AircraftMover
{
	AircraftMover(float vx, float vy, float vz, float rx, float ry, float rz) :
		velocity(vx, vy, vz), rotationX(rx), rotationY(ry), rotationZ(rz)
	{
	}
	void operator() (SceneNode& node, GameTimer) const
	{
		Aircraft& aircraft = static_cast<Aircraft&>(node);
		aircraft.setVelocity(velocity);
		aircraft.setWorldRotation(rotationX, rotationY, rotationZ);
	}
	XMFLOAT3 velocity;
	float rotationX;
	float rotationY;
	float rotationZ;
};

class Player : public Entity
{
public:
	Player(Game* game);


private:
	virtual void		drawCurrent() const;
	virtual void		buildCurrent();

public:

	void				handleEvent(InputCommandQueue& commands,const GameTimer& gt);
	void				handleRealtimeInput(InputCommandQueue& commands);
	void				Move();
	void				UpdateCurrent(const GameTimer& gt);

private:
	std::string			mSprite;
};

