#include "stdafx.h"

namespace SpaceWar
{
	Ship::Ship(double x, double y, double angle, double hp, double speed, double crange,
		String key, Side side, Shield::Type type) :
		Ship(x, y, angle, hp, 0.0, speed, crange, key, side, type)
	{

	}

	Ship::Ship(Vec2 xy, double angle, double hp, double speed, double crange,
		String key, Side side, Shield::Type type) :
		Ship(xy.x, xy.y, angle, hp, speed, crange, key, side, type)
	{

	}

	Ship::Ship(double x, double y, double angle, double hp, double shield, double speed,
		double crange, String key, Side side, Shield::Type type) :
		ObjectParam(x, y, SHIP_SCALE, angle, hp, shield, speed, crange, key,
			Ellipse{ x, y, TextureAsset(key).size() / 2 * 0.08 }, side, type),
		sp_(x, y, angle), tp_(x, y, angle), mtime_(0.0)
	{
	
	}

	Ship::Ship(Vec2 xy, double angle, double hp, double shield, double speed, double crange,
		String key, Side side, Shield::Type type) :
		Ship(xy.x, xy.y, angle, hp, shield, speed, crange, key, side, type)
	{

	}

	void Ship::update()
	{
		//基本描画
		draw();

		//現座標がターゲット座標の指定範囲内に入っていない場合
		if (not Circle{ getTargetPos(), 10 }.intersects(xy_()))
			//ターゲット座標に向けて角度を調整
			move();
		//移動中でないとき敵が可認知範囲にいればそちらに方向を変える
		else
		{
			//可認知範囲内のうち自身と敵対するオブジェクトを格納したグループオブジェクト
			ObjectGroup group = GlobalVar::group.chkAreaCR(this).chkHostileSelf(this);

			//最寄りのオブジェクトをオブジェクト群から抽出
			Object* nearObj = nearest(*this, group);

			if (nearObj != nullptr)
			{
				//最寄りのオブジェクトに向きを変える
				turn(*nearObj);
				//銃オブジェクトを有効化する
				for (auto i : step(guns_.size()))
					guns_[i]->active_ = true;
			}
			else
			{
				//銃オブジェクトを無効化
				for (auto i : step(guns_.size()))
					guns_[i]->active_ = false;
			}
		}

		//銃オブジェクトを更新する
		for (auto i : step(guns_.size()))
			guns_[i]->update();

		//サブクラス描画
		ObjectParam::update();

		//ゲージ描画
		drawGauge();
	}

	void Ship::draw()
	{
		//アクティブ状態なら点滅描画
		if (active_)
			texture_.scaled(scale_).rotated(ToRadians(angle_ + 90)).drawAt(xy_(),
				ColorF{1 + 5 * Periodic::Sine0_1(1s), 1.0});
		else
			texture_.scaled(scale_).rotated(ToRadians(angle_ + 90)).drawAt(xy_());
	}

	void Ship::setTargetPos(double x, double y)
	{
		sp_.set(x_, y_, angle_);
		tp_.set(x, y, Atan2_deg(sp_.xy(), Vec2{ x, y }));
	}

	void Ship::setTargetPos(Vec2 xy)
	{
		setTargetPos(xy.x, xy.y);
	}

	Vec2 Ship::getTargetPos()
	{
		return tp_.xy();
	}

	void Ship::turn(double diff)
	{
		//偏角の正負によって移動させる方向を変える
		if (diff > 2)
			angle_ += mtime_ + Abs(diff / 60);
		else if (diff < -2)
			angle_ -= mtime_ + Abs(diff / 60);
	}

	void Ship::turn(Object obj)
	{
		turn(lerpAngle(angle_, Atan2_deg(xy_(), obj.xy_()), 1.0));
	}

	void Ship::move()
	{
		//始点と終点　どれくらい進んだかを示す指数
		double idx = (1.0 - Distance(xy_(), tp_.xy()) / Distance(sp_.xy(), tp_.xy())) * Math::PiF;
		//指数が負（始点よりも後ろの座標）になったら始点を現在座標に更新
		if (idx < 0) sp_.set(x_, y_, angle_);

		//移動モーション関数
		const double e = Sin(idx / 2) * Pow(Cos(idx / 2), 2);
		
		//目標座標と現在座標の偏角
		const double diff = lerpAngle(angle_, tp_.angle_, 1.0);

		//距離補正（突き抜け防止）
		double dsCor = Distance(sp_.xy(), tp_.xy()) / 100;
		//補正値が1以上ならば1に正規化
		if (dsCor > 1.0) dsCor = 1.0;

		//移動用時間管理関数
		mtime_ = Scene::DeltaTime() * 60 * speed_;

		//偏角分オブジェクトの角度を変化させる
		turn(diff);

		//ターゲット角度に向けてxy座標を進める
		x_ += Cos(ToRadians(angle_)) * mtime_ * (6 * e + 0.2) * dsCor;
		y_ += Sin(ToRadians(angle_)) * mtime_ * (6 * e + 0.2) * dsCor;

		//ターゲット座標への角度を更新する
		tp_.angle_ = Atan2_deg(xy_(), tp_.xy());
	}

	void Ship::drawGauge()
	{
		ObjectParam::drawGauge(x_, y_ - 50, 50);
	}

	void Ship::addGun(double ox, double oy, double damage, double interval, double speed,
		double duration, String key)
	{
		Gun* gun = new Gun{ x_, y_, ox, oy, angle_, damage, interval, speed, duration, key,
			GlobalVar::shotColor[key], getSide() };
		//銃オブジェクトを追加
		guns_ << gun;

		//ハッシュテーブルに登録
		GlobalVar::parentTable.add(gun, this);
	}

	void Ship::addGun(Vec2 oxy, double damage, double interval, double speed, double duration, String key)
	{
		addGun(oxy.x, oxy.y, damage, interval, speed, duration, key);
	}

	Gun* Ship::getGun(int32 n)
	{
		return guns_[n];
	}

	int32 Ship::sizeGun()
	{
		return guns_.size();
	}
}
