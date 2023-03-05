#include "stdafx.h"

namespace SpaceWar
{
	Map::Map() : width_(0),  height_(0)
	{

	}

	Map::Map(double x, double y) :
		Object(x, y), width_(MAP_WIDTH), height_(MAP_HEIGHT)
	{
		
	}

	Map::Map(Vec2 xy) :
		Map(xy.x, xy.y)
	{

	}

	void Map::update()
	{
		//ミニマップ基盤表示
		RectF{ xy_(), width_, height_}.draw(ColorF{0.0, 0.2, 0.8, 0.5});

		//ミニマップ縮尺
		double mapScale = static_cast<double>(width_) / VALID_WIDTH;

		//ミニマップ2Dレンダー作成
		const Transformer2D t{ Mat3x2::Scale(mapScale).translated(xy_()) };
		
		//カメラ表示
		Rect{ Arg::center(GlobalVar::camera.getCenter().asPoint()), WINDOW_WIDTH, WINDOW_HEIGHT }.
			draw(ColorF{ 1.0, 0.0, 0.0, 0.5 });

		//惑星位置表示
		for (auto i : step(GlobalVar::group.sizePlanet()))
			RectF{ GlobalVar::group.getPlanet(i)->xy_(), 5 / mapScale, 5 / mapScale}.draw(ColorF{1.0, 0.0, 0.0});

		//艦隊位置表示
		for (auto i : step(GlobalVar::group.sizeShip()))
			Circle( GlobalVar::group.getShip(i)->xy_(), 2 / mapScale).draw(ColorF{0.0, 1.0, 0.0});

		//弾位置表示
		for (auto i : step(GlobalVar::group.sizeShot()))
			Circle{ GlobalVar::group.getShot(i)->xy_(), 1 / mapScale }.draw(ColorF{ 1.0, 0.0, 0.0 });
	}
}
