#pragma once

namespace SpaceWar
{
	class Shield : public ObjectSide
	{
	private:

		//private変数宣言

		StopwatchA stopwatch_;
		//強化シールド用テクスチャ
		Texture* Rtext_;
	public:

		enum class Type : int8
		{
			Lv1,
			Lv1R,
			Lv2,
			Lv2R,
			Lv3,
			Lv3R
		};

		enum class State : int8
		{
			Advance,
			Normal,
			None
		};

		//public変数宣言

		//シールド値の参照
		double& hp_;
		//シールドのタイプ
		Type type_;
		//現在のシールドの状態
		State state_;

		//public関数宣言

		Shield(double, double, double, double&, String, Side, Type);

		//更新を行う
		void update();
		//シールドを破壊し一定時間無効化する
		void crack();
		//強化シールドが存在しているかどうかを取得する
		bool isRshield();
	};
}

