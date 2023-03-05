#pragma once

namespace SpaceWar
{
	class BackGround
	{
	private:

		//privateメンバ変数宣言

		//背景上の星を描画するためのリスト
		Array<Circle> stars_;
		//星の数
		int32 sNum_;

	public:

		//publicメンバ変数宣言

		//ステージ幅
		int width_;
		//ステージ高さ
		int height_;			

		//publicメンバ関数宣言

		BackGround();
		void update();

	};
}
