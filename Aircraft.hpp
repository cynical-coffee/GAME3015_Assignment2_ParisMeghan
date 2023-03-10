#pragma once
#include "Entity.hpp"
#include <string>

class Aircraft :
    public Entity
{
public:
	enum Type
	{
		Eagle,
		Raptor,
	};

public:
	Aircraft(Type type, Game* game);

	void					Move(float neg, float pos, float speed);
	virtual unsigned int	getCategory() const;

private:
	virtual void			drawCurrent() const;
	virtual void			buildCurrent();

private:
	Type					mType;
	std::string				mSprite;
};
