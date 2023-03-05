#pragma once

namespace SpaceWar
{
	class Gun
	{
	private:

		//private変数宣言

		//発射する弾の派閥
		Side side_;

		//銃弾間隔時間計測用
		StopwatchA stopwatch_;

		//弾の発射ステータス
		double& x_;
		double& y_;
		double& angle_;
		//座標補正値
		double ox_;
		double oy_;

		//弾発射時のエフェクト色
		ColorF color_;

	public:

		//public変数宣言

		//発射する銃弾のダメージ
		double damage_;
		//発射する銃弾の間隔
		double interval_;
		//発射する銃弾の速度
		double speed_;
		//発射する銃弾の持続時間
		double duration_;
		//発射する銃弾のアセットキー
		String key_;
		//弾を発射するかどうか
		bool active_;

		//public関数宣言

		Gun(double&, double&, double, double, double&, double, double, double, double,
			String, ColorF, Side = Side::Friend);

		//更新を行う
		void update();

		//銃弾を一回分発射する
		void fire();

		//弾発射時のエフェクト色を取得する
		ColorF getColor();
		//弾発射時のエフェクト色を設定する
		void setColor(ColorF);

	};
}

