#pragma once

namespace SpaceWar
{
	class Ship : public ObjectParam
	{
	private:

		//private変数宣言

		//移動開始座標・角度
		Pos3 sp_;

		//移動目標座標・角度（ターゲット座標・角度）
		Pos3 tp_;

		//移動用・時間計測変数
		double mtime_;

		//艦隊の使用する銃
		Array<Gun*> guns_;

	public:

		//public関数宣言

		Ship(double, double, double, double, double, double, String, Side = Side::Friend,
			Shield::Type = Shield::Type::Lv1);
		Ship(Vec2, double, double, double, double, String, Side = Side::Friend,
			Shield::Type = Shield::Type::Lv1);
		Ship(double, double, double, double, double, double, double, String, Side = Side::Friend,
			Shield::Type = Shield::Type::Lv1);
		Ship(Vec2, double, double, double, double, double, String, Side = Side::Friend,
			Shield::Type = Shield::Type::Lv1);

		//更新を行う
		void update();
		//描画を行う
		void draw();

		//ターゲット座標を設定する
		void setTargetPos(double, double);
		void setTargetPos(Vec2);
		//ターゲット座標を取得する
		Vec2 getTargetPos();

		//指定された偏角分オブジェクトの角度を変化させる
		void turn(double);
		//指定したオブジェクトの方向へ角度を変化させる
		void turn(Object);

		//オブジェクトの移動を行う
		void move();

		//ゲージの描画を行う
		void drawGauge();

		//艦隊の使用する銃を追加する
		void addGun(double, double, double, double, double, double, String);
		void addGun(Vec2, double, double, double, double, String);

		//指定した要素の銃オブジェクトを取得する
		Gun* getGun(int32);
		//銃オブジェクトのサイズを取得する
		int32 sizeGun();
	};
}
