#include "stdafx.h"

namespace SpaceWar
{
	Shot::Shot(double x, double y, double angle, double damage, double speed, double duration,
		String key, Side side) :
		ObjectSide(x, y, SHOT_SCALE, angle, key, Ellipse{ x, y, TextureAsset(key).size() * SHOT_SCALE / 4}, side),
		damage_(damage), speed_(speed), duration_(duration)
	{

	}

	Shot::Shot(Vec2 xy, double angle, double damage, double speed, double duration,
		String key, Side side) :
		Shot(xy.x, xy.y, angle, damage, speed, duration, key, side)
	{

	}

	void Shot::draw()
	{
		//当たり判定処理
		ObjectEllipseCD::update();

		//弾の描画
		texture_.scaled(scale_).rotated(ToRadians(angle_ + 90)).drawAt(xy_());

		//移動の処理
		move();
	}

	void Shot::move()
	{
		//角度方向に直進する
		x_ += Cos(ToRadians(angle_)) * speed_;
		y_ += Sin(ToRadians(angle_)) * speed_;
	}
}
