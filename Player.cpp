#include "Player.h"
#include "Game.hpp"

Player::Player( Game* game): Entity(game)
{
	mSprite = "Eagle";
}

void Player::drawCurrent() const
{
	/*renderer->World = getTransform();
	renderer->NumFramesDirty++;*/
}

void Player::buildCurrent()
{
	auto render = std::make_unique<RenderItem>();
	renderer = render.get();
	renderer->World = getTransform();
	renderer->ObjCBIndex = game->getRenderItems().size();
	renderer->Mat = game->getMaterials()[mSprite].get();
	renderer->Geo = game->getGeometries()["boxGeo"].get();
	renderer->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	renderer->IndexCount = renderer->Geo->DrawArgs["box"].IndexCount;
	renderer->StartIndexLocation = renderer->Geo->DrawArgs["box"].StartIndexLocation;
	renderer->BaseVertexLocation = renderer->Geo->DrawArgs["box"].BaseVertexLocation;

	game->getRenderItems().push_back(std::move(render));
}

void Player::handleEvent(InputCommandQueue& commands,const GameTimer& gt)
{
	float playerSpeed = 2.f;

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		Command moveUp;
		moveUp.category = Category::PlayerAircraft;
		moveUp.action = derivedAction<Aircraft>(AircraftMover(0.0f, 0.5f, 0, 0.1f, XM_PI, 0.0f));
		commands.push(moveUp);
	}
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		Command moveDown;
		moveDown.category = Category::PlayerAircraft;
		moveDown.action = derivedAction<Aircraft>(AircraftMover(0.0f, -0.5f, 0, -0.1f, XM_PI, 0.0f));
		commands.push(moveDown);
	}
	else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		Command moveLeft;
		moveLeft.category = Category::PlayerAircraft;
		moveLeft.action = derivedAction<Aircraft>(AircraftMover(playerSpeed, 0.0f, 0.0f, 0.0f, XM_PI, -0.1f));
		commands.push(moveLeft);
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		Command moveRight;
		moveRight.category = Category::PlayerAircraft;
		moveRight.action = derivedAction<Aircraft>(AircraftMover(-playerSpeed, 0.f, 0.0f, 0.0f, XM_PI, 0.1f));
		commands.push(moveRight);
	}
	else
	{
		Command moveStop;
		moveStop.category = Category::PlayerAircraft;
		moveStop.action = derivedAction<Aircraft>(AircraftMover(0, 0, 0, 0.0f, XM_PI, 0.0f));
		commands.push(moveStop);
	}
}

void Player::handleRealtimeInput(InputCommandQueue& commands)
{
}

void Player::Move()
{
	if (this->getWorldPosition().x < -1.5f)
	{
		this->setVelocity(1.0f, 0.0f, 0.0f);
		this->setWorldRotation(0.0f, XM_PI, -0.1f);
		
	}
	if (this->getWorldPosition().x > 1.5f)
	{
		this->setVelocity(-1.0f, 0.0f, 0.0f);
		this->setWorldRotation(0.0f, XM_PI, 0.1f);
	}
}

void Player::UpdateCurrent(const GameTimer& gt)
{
	
}


