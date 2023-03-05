#pragma once

namespace SpaceWar
{
	class Shot : public ObjectSide
	{
	public:

		//publicメンバ関数

		//弾接触時のダメージ
		double damage_;
		//弾の移動速度
		double speed_;
		//弾の持続時間
		double duration_;

		//弾持続時間計測用
		StopwatchA stopwatch_;

		//publicメンバ関数

		Shot(double, double, double, double, double, double, String, Side = Side::Friend);
		Shot(Vec2, double, double, double, double, String, Side = Side::Friend);

		//オブジェクトの描画を行う
		void draw();
		//オブジェクトの移動を行う
		void move();
	};
}

