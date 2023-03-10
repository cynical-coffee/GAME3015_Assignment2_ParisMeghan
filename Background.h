#pragma once
#include "Entity.hpp"

class Background : public Entity
{
public:
	Background(Game* game);
	unsigned getCategory() const override;
	void Repeat(float endDist, float startPos);


private:
	void drawCurrent() const override;
	void buildCurrent() override;

public:
	void updateCurrent(const GameTimer& gt) override;

private:
	std::string				mSprite;
};

