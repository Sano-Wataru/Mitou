#include "stdafx.h"

namespace SpaceWar
{
	ObjectEllipseCD::ObjectEllipseCD(double x, double y, double scale, double angle, String key, Ellipse cd) :
		ObjectPic(x, y, scale, angle, key), cd_(cd)
	{

	}

	void ObjectEllipseCD::update()
	{
		//当たり判定を現在座標へ設定
		setCD(xy_());

		//当たり判定表示が有効ならば楕円フレームを描画
		if (GlobalVar::visibleCD) cd_.drawFrame(3, Palette::Aquamarine);
	}

	void ObjectEllipseCD::setCD(double x, double y, double a, double b)
	{
		cd_.x = x;
		cd_.y = y;
		cd_.a = a;
		cd_.b = b;
	}

	void ObjectEllipseCD::setCD(Vec2 xy, Vec2 ab)
	{
		setCD(xy.x, xy.y, ab.x, ab.y);
	}

	void ObjectEllipseCD::setCD(double x, double y)
	{
		setCD(x, y, cd_.a, cd_.b);
	}

	void ObjectEllipseCD::setCD(Vec2 xy)
	{
		setCD(xy, cd_.axes);
	}

	Ellipse ObjectEllipseCD::getCD()
	{
		return cd_;
	}
}
