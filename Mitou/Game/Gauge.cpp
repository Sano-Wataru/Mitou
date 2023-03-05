#include "stdafx.h"

namespace SpaceWar
{
	Gauge::Gauge(double x, double y, double width, double height, double param, double mparam, Color color) :
		Object(x, y), gauge_(Arg::center(x, y), width, height), frame_(Arg::center(x, y), width, height),
		color_(color), mw_(width), param_(param), mparam_(mparam)
		
	{

	}

	Gauge::Gauge(Vec2 xy, Vec2 size, double param, double mparam, Color color) :
		Gauge(xy.x, xy.y, size.x, size.y, param, mparam, color)
	{

	}

	void Gauge::draw()
	{
		gauge_.setSize(mw_ * param_ / mparam_, gauge_.h);
		gauge_.draw(color_);
		frame_.drawFrame(0.5, 1, Palette::White, Palette::Gray);
	}
}
