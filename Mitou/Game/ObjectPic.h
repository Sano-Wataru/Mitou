#pragma once

namespace SpaceWar
{
	class ObjectPic : public Object
	{
	public:

		//public変数宣言

		//画像表示用
		Texture texture_;

		//画像縮尺
		double scale_;
		//画像角度
		double angle_;

		//アセットシンボル
		AssetSym asset_;

		//public関数宣言

		//コンストラクタ
		ObjectPic(double, double, double, double, String);

	};
}
