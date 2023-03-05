#pragma once

namespace SpaceWar
{
	class ObjectSide : public ObjectEllipseCD
	{
	private:

		//private変数宣言

		//派閥　友好:Friend 敵対:Enemy Neutral:中立
		Side side_;

	public:

		//public関数宣言

		ObjectSide(double, double, double, double, String, Ellipse, Side);

		//派閥を友好にする
		void setSideFriend();
		//派閥を敵対にする
		void setSideHostile();
		//派閥を中立にする
		void setSideNeutral();
		//派閥を取得する
		Side getSide();

		//指定したオブジェクトが自身と敵対するオブジェクトであるか判定する
		template <class TObj>
		bool chkHostileSelf(TObj);
	};
}

