#include "stdafx.h"

namespace SpaceWar
{
	Shield::Shield(double x, double y, double scale, double& hp, String key, Side side, Type type) :
		ObjectSide(x, y, scale, 0.0, key, Ellipse{ x, y, TextureAsset(key).size() * scale * 0.35}, side),
		hp_(hp), type_(type), Rtext_(nullptr), state_(State::Normal)
	{
		//強化シールドのアセット確定
		String t_key = U"";

		switch (type_)
		{
		case Type::Lv1R:
			t_key = U"ShieldR1";
			break;

		case Type::Lv2R:
			t_key = U"ShieldR2";
			break;

		case Type::Lv3R:
			t_key = U"ShieldR3";
			break;
		}

		//強化シールドが存在するならば
		if (t_key != U"")
		{
			//テクスチャ割り当て
			Rtext_ = new TextureAsset(t_key);

			//当たり判定変更
			setCD(xy_(), getCD().axes * 1.3);

			//状態を強化シールド状態に
			state_ = State::Advance;
		}
	}

	void Shield::update()
	{
		//通常シールド縮尺アニメーション
		double scale = scale_ + scale_ / 30.0 * Periodic::Sine1_1(2s);

		//強化シールド縮尺アニメーション
		double rscale = scale_ + scale_ / 30.0 * Periodic::Sine1_1(3s);

		//シールドが有効状態ならば
		if (state_ != State::None)
		{
			//基本描画
			texture_.scaled(scale).drawAt(xy_());

			//強化シールド状態だったら
			if (state_ == State::Advance)
			{
				//強化シールドの描画を行う
				Rtext_->scaled(rscale).drawAt(xy_());
			}

			//当たり判定描画
			ObjectEllipseCD::update();
		}
	}

	void Shield::crack()
	{
		//エフェクト描画
		ColorF color;

		//破片飛び散り半径
		double radius;

		//範囲確定
		if (state_ == State::Advance)
			radius = Rtext_->width() / 2.0 * scale_ * 0.8;
		else if (state_ == State::Normal)
			radius = texture_.width() / 2.0 * scale_ * 0.8;

		//レベルごとに破片の色を変える
		if (type_ == Type::Lv2 || type_ == Type::Lv2R)
			color = COLOR_FRAGMENT_LV2;
		else if (type_ == Type::Lv3 || type_ == Type::Lv3R)
			color = COLOR_FRAGMENT_LV3;
		else
			color = COLOR_FRAGMENT_LV1;

		//エフェクト描画
		GlobalVar::effect->add<GameEffect::CrackEffect>(xy_(), radius, 500, color);

		//状態が強化シールドの場合
		if (state_ == State::Advance)
		{
			//当たり判定を元に戻す
			setCD(xy_(), getCD().axes * 1.0 / 1.3);

			//シールドを通常にする
			state_ = State::Normal;
		}
		else
			//シールドを無効化
			state_ = State::None;
	}

	bool Shield::isRshield()
	{
		return Rtext_ == nullptr ? false : true;
	}
}
