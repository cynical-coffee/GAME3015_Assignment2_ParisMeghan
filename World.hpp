#pragma once
#include "SceneNode.hpp"
#include "Aircraft.hpp"
#include "InputCommandQueue.h"
#include "Player.h"
#include "SpriteNode.h"
#include "Background.h"

class World 
{
public:
	explicit							World(Game* window);
	void								update(const GameTimer& gt);
	void								draw();
	void								buildScene();
	InputCommandQueue&					getCommandQueue();
	
private:
	enum Layer
	{
		Terrain,
		Air,
		LayerCount
	};


private:
	Game*								mGame;

	SceneNode*							mSceneGraph;
	std::array<SceneNode*, LayerCount>	mSceneLayers;
	InputCommandQueue					mCommandQueue;
	XMFLOAT4							mWorldBounds;
	XMFLOAT2		    				mSpawnPosition;
	XMFLOAT3							mScrollSpeed;
	Aircraft*							mPlayerAircraft;
	Aircraft*							mEnemy1;
	Aircraft*							mEnemy2;
	Player*								mPlayer;
	Background*							mTerrain;
};
