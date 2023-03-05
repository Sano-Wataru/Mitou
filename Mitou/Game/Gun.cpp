#include "stdafx.h"

namespace SpaceWar
{
	Gun::Gun(double& x, double& y, double ox, double oy, double& angle, double damage, double interval,
		double speed, double duration, String key, ColorF color, Side side) :
		damage_(damage), interval_(interval), speed_(speed), duration_(duration), key_(key), side_(side),
		x_(x), y_(y), angle_(angle), ox_(ox), oy_(oy), color_(color)
	{

	}

	void Gun::update()
	{
		//発射間隔分の秒数がたったら弾を発射
		if (active_ && stopwatch_.watchState(interval_))
			fire();
	}

	void Gun::fire()
	{
		double r = sqrt(pow(ox_, 2) + pow(oy_, 2));
		double theta = ToRadians(angle_ + 90 + ToDegrees(Atan2(Vec2{ x_, y_ }, Vec2{ x_ + ox_, y_ - oy_ })));

		Shot* shot = new Shot{ x_ + r * Cos(theta), y_ + r * Sin(theta),
			angle_, damage_, speed_, duration_, key_, side_ };

		//弾オブジェクト追加
		GlobalVar::group.addShot(shot);

		//ハッシュテーブルに登録
		GlobalVar::parentTable.add(shot, this);

		//エフェクト表示
		GlobalVar::effect->add<GameEffect::ShotEffect>(Vec2{ x_ + r * Cos(theta), y_ + r * Sin(theta)}, color_);
	}

	ColorF Gun::getColor()
	{
		return color_;
	}

	void Gun::setColor(ColorF color)
	{
		color_ = color;
	}
}
