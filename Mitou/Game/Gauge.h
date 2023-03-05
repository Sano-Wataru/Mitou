#pragma once

namespace SpaceWar
{
	class Gauge : public Object
	{
	private:

		//private変数宣言

		RectF gauge_;
		RectF frame_;
		Color color_;
		//ゲージ幅初期値
		double mw_;

		//パラメータ現在値
		double param_;
		//パラメータ最大値
		double mparam_;

	public:

		//public関数宣言

		Gauge(double, double, double, double, double, double, Color);
		Gauge(Vec2, Vec2, double, double, Color);

		void draw();
	};
}

