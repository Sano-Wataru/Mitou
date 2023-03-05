#include "stdafx.h"

namespace SpaceWar
{
	Pos3::Pos3(double x, double y, double angle) : x_(x), y_(y), angle_(angle)
	{

	}

	Vec2 Pos3::xy()
	{
		return Vec2{ x_, y_ };
	}

	void Pos3::set(double x, double y, double angle)
	{
		set(x, y);
		set(angle);
	}

	void Pos3::set(double x, double y)
	{
		x_ = x;
		y_ = y;
	}

	void Pos3::set(double angle)
	{
		angle_ = angle;
	}
}
