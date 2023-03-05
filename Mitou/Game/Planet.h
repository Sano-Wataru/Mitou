#pragma once

namespace SpaceWar
{
	class Planet : public ObjectParam
	{
	public:

		//publicメンバ関数宣言
		Planet(double, double, double, double, double, String, Side = Side::Friend,
			Shield::Type = Shield::Type::Lv1);
		Planet(Vec2, double, double, double, String, Side = Side::Friend,
			Shield::Type = Shield::Type::Lv1);
		Planet(double, double, double, double, double, double, String, Side = Side::Friend,
			Shield::Type = Shield::Type::Lv1);
		Planet(Vec2, double, double, double, double, String, Side = Side::Friend,
			Shield::Type = Shield::Type::Lv1);

		void update();

		//ゲージの描画を行う
		void drawGauge();
	};
}

