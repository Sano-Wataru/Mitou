#include "stdafx.h"

namespace SpaceWar
{
	Object::Object() : x_(0.0), y_(0.0)
	{

	}

	Object::Object(double x, double y) : x_(x), y_(y)
	{

	}

	void Object::xy_(Vec2 xy)
	{
		x_ = xy.x;
		y_ = xy.y;
	}

	Vec2 Object::xy_()
	{
		return Vec2{ x_, y_ };
	}
}
