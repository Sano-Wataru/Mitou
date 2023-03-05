#pragma once

namespace SpaceWar
{
	class Object
	{
	public:

		//publicメンバ変数宣言

		double x_;
		double y_;

		//publicメンバ関数宣言

		//コンストラクタ
		Object();
		Object(double, double);

		//オブジェクトのxy座標を設定する
		void xy_(Vec2);
		//オブジェクトのxy座標を返す
		Vec2 xy_();
	};
}

