#include "stdafx.h"

namespace SpaceWar
{
	ObjectSide::ObjectSide(double x, double y, double scale, double angle, String key, Ellipse cd, Side side) :
		ObjectEllipseCD(x, y, scale, angle, key, cd), side_(side)
	{

	}

	void ObjectSide::setSideFriend()
	{
		side_ = Side::Friend;
	}

	void ObjectSide::setSideHostile()
	{
		side_ = Side::Hostile;
	}

	void ObjectSide::setSideNeutral()
	{
		side_ = Side::Neutral;
	}

	Side ObjectSide::getSide()
	{
		return side_;
	}

	template <class TObj>
	bool ObjectSide::chkHostileSelf(TObj obj)
	{
		if (getSide() == Side::Friend && obj.getSide() == Side::Hostile)
			return true;
		else if (getSide() == Side::Hostile && obj.getSide() == Side::Friend)
			return true;
		else
			return false;
	}

	template bool ObjectSide::chkHostileSelf<ObjectSide>(ObjectSide);
	template bool ObjectSide::chkHostileSelf<Planet>(Planet);
	template bool ObjectSide::chkHostileSelf<Ship>(Ship);
	template bool ObjectSide::chkHostileSelf<Shot>(Shot);
}
