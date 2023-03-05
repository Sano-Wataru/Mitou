#pragma once

namespace SpaceWar
{
	class Map : public Object
	{

	public:

		//public変数宣言

		int32 width_;
		int32 height_;

		//public関数宣言
		Map();
		Map(double, double);
		Map(Vec2);

		void update();
	};
}

