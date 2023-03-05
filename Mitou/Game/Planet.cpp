#include "stdafx.h"

namespace SpaceWar
{
	Planet::Planet(double x, double y, double scale, double hp, double crange,
		String key, Side side, Shield::Type type) :
		Planet(x, y, scale, hp, 0.0, crange, key, side, type)
	{

	}

	Planet::Planet(Vec2 xy, double scale, double hp, double crange,
		String key, Side side, Shield::Type type) :
		Planet(xy.x, xy.y, scale, hp, crange, key, side, type)
	{

	}

	Planet::Planet(double x, double y, double scale, double hp, double shield, double crange,
		String key, Side side, Shield::Type type) :
		ObjectParam(x, y, scale, 0.0, hp, shield, 0.0, crange, key,
			Ellipse{ Vec2{ x, y }, TextureAsset(key).size() / 2 * 0.4 }, side, type)
	{
		
	}

	Planet::Planet(Vec2 xy, double scale, double hp, double shield, double crange,
		String key, Side side, Shield::Type type) :
		Planet(xy.x, xy.y, scale, hp, shield, crange, key, side, type)
	{

	}

	void Planet::update()
	{
		//基本描画
		texture_.scaled(scale_).drawAt(xy_());

		//サブクラス描画
		ObjectParam::update();

		//ゲージ描画
		drawGauge();
	}

	void Planet::drawGauge()
	{
		ObjectParam::drawGauge(x_, y_ + 60, 150);
	}
}
