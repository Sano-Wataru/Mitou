#pragma once

namespace SpaceWar
{
	class ObjectParam : public ObjectSide
	{
	private:
		//privateメンバ変数宣言

		//オブジェクトの最大体力値
		double mhp_;
		//オブジェクトの最大シールド値
		double mshield_;
		//シールドオブジェクト
		Shield* sobj_;

		//privateメンバ関数宣言

		void drawShield();
		void chkDamaged();

	public:

		//publicメンバ変数宣言

		//オブジェクトの体力値
		double hp_;
		//オブジェクトのシールド値
		double shield_;
		//オブジェクトの速度
		double speed_;
		//オブジェクトの可認知範囲
		double crange_;
		//オブジェクトアクティブ
		bool active_;

		//publicメンバ関数宣言

		//コンストラクタ
		ObjectParam(double, double, double, double, double, double, double, double, String, Ellipse,
			Side, Shield::Type);

		//更新を行う
		void update();

		//最大体力値を取得する
		double getMaxHP();
		////最大シールド値を取得する
		double getMaxSHIELD();

		//ゲージを描画する
		void drawGauge(double, double, double);
	};
}
