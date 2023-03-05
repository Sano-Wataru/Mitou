#include "stdafx.h"

namespace SpaceWar
{
	ObjectParam::ObjectParam(double x, double y, double scale, double angle, double hp, double shield,
		double speed, double crange, String key, Ellipse cd, Side side, Shield::Type type) :
		ObjectSide(x, y, scale, angle, key, cd, side), hp_(hp), shield_(shield), speed_(speed), crange_(crange),
		active_(false), mhp_(hp), mshield_(shield), sobj_(nullptr)
	{
		//シールドが存在するならばシールドオブジェクトを作成
		if (mshield_ > 0)
		{
			double t_scale = PLANET_SHIELD_SCALE;
			String t_key = U"Shield1";

			//シールドの縮尺確定（惑星・艦隊）
			if (asset_.tag_.contains(U"Ship"))
				t_scale = SHIP_SHIELD_SCALE;

			//シールドのレベル確定
			if (type == Shield::Type::Lv2 || type == Shield::Type::Lv2R)
				t_key = U"Shield2";
			else if (type == Shield::Type::Lv3 || type == Shield::Type::Lv3R)
				t_key = U"Shield3";

			//シールドオブジェクト作成
			sobj_ = new Shield{ x, y, t_scale, shield, t_key, side, type };
		}
	}

	void ObjectParam::update()
	{
		//敵の弾接触時にダメージを受ける
		chkDamaged();

		//シールド値が存在すれば描画
		if (mshield_ > 0)
			drawShield();

		//当たり判定を更新
		ObjectEllipseCD::update();

		//可認知範囲表示が有効ならば円フレームを描画
		if (GlobalVar::visibleCR) Circle{ xy_(), crange_ }.drawFrame(3, Palette::Magenta);
	}

	double ObjectParam::getMaxHP()
	{
		return mhp_;
	}

	double ObjectParam::getMaxSHIELD()
	{
		return mshield_;
	}

	void ObjectParam::chkDamaged()
	{
		//当たり判定に接触した弾オブジェクトを取得
		Array<Shot*> shots;

		//シールドが存在するならばシールドの当たり判定を利用
		if (shield_ > 0)
			shots = GlobalVar::group.getTouchShot(sobj_);
		//シールドがなければ自分自身の当たり判定を利用
		else
			shots = GlobalVar::group.getTouchShot(this);

		for (auto it = shots.begin(); it != shots.end();)
		{
			//イテレータをポインタに変換
			Shot* tmp = *it;

			//接触した弾が自分と敵対する弾だったら
			if (chkHostileSelf(*tmp))
			{
				//シールドゲージがあった場合
				if (shield_ > 0)
				{
					shield_ -= tmp->damage_;

					//シールドゲージが０を超えて下回った場合は０に補正
					if (shield_ < 0)
						shield_ = 0;
				}
				//なかった場合はHPを減らす
				else
					hp_ -= tmp->damage_;

				//エフェクト描画
				GlobalVar::effect->add<GameEffect::SparkEffect>(tmp->xy_());

				//オブジェクトリストから削除
				it = shots.erase(it);
				GlobalVar::group.deleteShot(tmp);

				break;
			}
			//イテレータを進める
			++it;
		}
	}

	void ObjectParam::drawGauge(double x, double y, double width)
	{
		//HPゲージ
		Gauge{ x, y, width, 6, hp_, mhp_, COLOR_HP_GAUGE }.draw();

		//シールドが存在する場合
		if (sobj_ != nullptr)
		{
			//通常シールド状態であれば
			if (sobj_->state_ == Shield::State::Normal)
				Gauge{ x, y + 10, width, 6, shield_, mshield_, COLOR_SHIELD_GAUGE }.draw();

			//強化シールド状態であれば
			if (sobj_->state_ == Shield::State::Advance)
			{
				//通常シールドゲージは常に最大値を記録する
				Gauge{ x, y + 10, width, 6, mshield_, mshield_, COLOR_SHIELD_GAUGE }.draw();
				//強化シールドゲージ
				Gauge{ x, y + 10, width, 6, shield_, mshield_, COLOR_RSHIELD_GAUGE }.draw();
			}
		}
	}

	void ObjectParam::drawShield()
	{
		//シールドオブジェクトの位置を更新
		sobj_->xy_(xy_());

		//シールドオブジェクトを更新
		sobj_->update();

		//シールド値が０以下・強化シールドなしでシールド破壊
		if (shield_ <= 0)
		{
			if (sobj_->state_ == Shield::State::Advance)
			{
				sobj_->crack();

				//シールド値を最大に戻す
				shield_ = mshield_;
			}
			else if (sobj_->state_ == Shield::State::Normal)
				sobj_->crack();
		}
	}
}
