#include "World.hpp"
#include <iostream>

World::World(Game* game)
	: mGame(game)
	, mSceneGraph(new SceneNode(game))
	, mWorldBounds(-1.5f, 1.5f, 200.0f, 0.0f)
	, mSpawnPosition(0.f, 0.f)
	, mScrollSpeed(-1.0f, 0.0f, 0) //Left, Right, Down, Up
	, mPlayerAircraft(nullptr)
	, mEnemy1(nullptr)
	, mEnemy2(nullptr)
	, mPlayer(nullptr)
	, mTerrain(nullptr)
{
}

void World::update(const GameTimer& gt)
{
	while (!mCommandQueue.isEmpty())
	{
		mSceneGraph->onCommand(mCommandQueue.pop(), gt);
	}

	if (mEnemy1->getWorldPosition().x < -1.0f)
	{
		mEnemy1->setVelocity(1.0f, 0.0f, 0.0f);
		mEnemy1->setWorldRotation(0.0f, XM_PI, -0.1f);
	}
	if (mEnemy1->getWorldPosition().x > 2.0f)
	{
		mEnemy1->setVelocity(-1.0f, 0.0f, 0.0f);
		mEnemy1->setWorldRotation(0.0f, XM_PI, 0.1f);
	}

	if (mEnemy2->getWorldPosition().x < -2.0f)
	{
		mEnemy2->setVelocity(1.0f, 0.0f, 0.0f);
		mEnemy2->setWorldRotation(0.0f, XM_PI, -0.1f);
	}
	if (mEnemy2->getWorldPosition().x > 1.0f)
	{
		mEnemy2->setVelocity(-1.0f, 0.0f, 0.0f);
		mEnemy2->setWorldRotation(0.0f, XM_PI, 0.1f);
	}

	mSceneGraph->update(gt);
}

void World::draw()
{
	mSceneGraph->draw();
}

void World::buildScene()
{
	std::unique_ptr<Aircraft> player(new Aircraft(Aircraft::Eagle, mGame));
	mPlayerAircraft = player.get();
	mPlayerAircraft->setPosition(0, 1, 0.0);
	mPlayerAircraft->setScale(0.5, 0.5, 0.5);
	mPlayerAircraft->setWorldRotation(0, XM_PI, 0.0f);
	mSceneGraph->attachChild(std::move(player));

	std::unique_ptr<Aircraft> enemy(new Aircraft(Aircraft::Raptor, mGame));
	mEnemy1 = enemy.get();
	mEnemy1->setPosition(0.5, 1.5, 0.5);
	mEnemy1->setScale(0.5, 0.5, 0.5);
	mEnemy1->setWorldRotation(0, XM_PI, 0.0f);
	mEnemy1->setVelocity(mScrollSpeed);
	mSceneGraph->attachChild(std::move(enemy));

	std::unique_ptr<Aircraft> enemy2(new Aircraft(Aircraft::Raptor, mGame));
	mEnemy2 = enemy2.get();
	mEnemy2->setPosition(-0.5, 1.5, 0.5);
	mEnemy2->setScale(0.5, 0.5, 0.5);
	mEnemy2->setWorldRotation(0, XM_PI, 0.0f);
	mEnemy2->setVelocity(mScrollSpeed);
	mSceneGraph->attachChild(std::move(enemy2));

	/*std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(mGame));
	mBackground = backgroundSprite.get();
	mBackground->setPosition(0, 0, 1.0);
	mBackground->setScale(100.0, 1.0, 300.0);
	mBackground->setVelocity(XMFLOAT3(0.0, 0.0, 8.0));
	mSceneGraph->attachChild(std::move(backgroundSprite));*/

	std::unique_ptr<Background> terrainSprite(new Background(mGame));
	mTerrain = terrainSprite.get();
	mTerrain->setPosition(0, 0, 1.0);
	mTerrain->setScale(300.0, 1.0, 300.0);
	mSceneGraph->attachChild(std::move(terrainSprite));

	mSceneGraph->build();
}

InputCommandQueue& World::getCommandQueue()
{
	return mCommandQueue;
}
