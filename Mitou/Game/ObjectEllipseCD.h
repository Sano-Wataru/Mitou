#pragma once

namespace SpaceWar
{
	class ObjectEllipseCD : public ObjectPic
	{
	private:

		//private変数宣言

		//当たり判定
		Ellipse cd_;

	public:

		//public関数宣言

		//コンストラクタ
		ObjectEllipseCD(double, double, double, double, String, Ellipse);

		//更新を行う
		void update();

		//当たり判定を設定する
		void setCD(double, double, double, double);
		void setCD(Vec2, Vec2);
		void setCD(double, double);
		void setCD(Vec2);
		//当たり判定を取得する
		Ellipse getCD();
	};
}
