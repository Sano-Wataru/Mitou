#pragma once

namespace SpaceWar
{
	class SelectRect
	{

	private:

		//private変数宣言

		//マウスドラッグ始点
		Vec2 sp_;
		//マウスドラッグ終点
		Vec2 ep_;
		//矩形色
		ColorF color_;
		//矩形フレーム色
		ColorF colorFrame_;
		//矩形オブジェクト
		RectF rect_;

	public:

		//public変数宣言

		bool active_;

		//public関数宣言

		SelectRect(ColorF = {SRC_DEFAULT}, ColorF = {SRC_DEFAULT_FRAME});

		//更新を行う
		void update();
		//中心座標を取得
		Vec2 getCenter();
		//左上座標を取得
		Vec2 getLeftUpper();
		//幅・高さを返す
		Vec2 getArea();

		//選択範囲内に指定した座標が含まれていたらtrue
		bool isArea(Vec2);
		//選択範囲内に指定したオブジェクトが含まれていたらtrue
		bool isArea(ObjectEllipseCD*);
		bool isArea(ObjectRectCD*);
	};
}

