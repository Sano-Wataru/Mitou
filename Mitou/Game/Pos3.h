#pragma once

namespace SpaceWar
{
	class Pos3
	{
	public:

		//public変数宣言

		double x_;
		double y_;
		double angle_;

		//public関数宣言

		Pos3(double, double, double);

		Vec2 xy();
		void set(double, double, double);
		void set(double, double);
		void set(double);

	};
}

