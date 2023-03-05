#include "stdafx.h"

namespace SpaceWar
{
	ObjectGroup::ObjectGroup() : planetInit_(nullptr)
	{
		
	}

	//更新を行う
	void ObjectGroup::update()
	{
		//惑星オブジェクトの描画
		for (auto it = planets_.begin(); it != planets_.end();)
		{
			Planet* tmp = *it;

			//HPが０以下だったら
			if (tmp->hp_ <= 0)
			{
				//オブジェクトを削除する
				it = planets_.erase(it);
				delete(tmp);
			}
			else
			{
				//オブジェクトを更新
				tmp->update();

				//イテレータを一つ進める
				it++;
			}
		}

		//艦隊オブジェクトの描画
		for (auto it = ships_.begin(); it != ships_.end();)
		{
			Ship* tmp = *it;

			//HPが０以下だったら
			if (tmp->hp_ <= 0)
			{
				//エフェクト追加
				GlobalVar::effect->add<GameEffect::ExplodeEffect>(tmp->xy_(), 40, 50);

				//オブジェクトを削除する
				it = ships_.erase(it);
				delete(tmp);
			}
			else
			{
				//オブジェクトを更新
				tmp->update();

				//イテレータを一つ進める
				it++;
			}
		}

		//弾オブジェクトの描画
		for (auto it = shots_.begin(); it != shots_.end();)
		{
			//イテレータを弾オブジェクトポインタに変換
			Shot* tmp = *it;

			//発射した弾を描画
			tmp->draw();

			//持続時間が経過したら弾を削除する
			if (tmp->stopwatch_.watchState(tmp->duration_))
			{
				//リストから該当オブジェクトを削除しイテレータを更新
				it = shots_.erase(it);

				//該当オブジェクト自体を削除
				delete(tmp);
			}
			else
				//削除がなければイテレータを進める
				it++;
		}
	}

	//オブジェクトの追加を行う
	template <class TObj>
	void ObjectGroup::add(Array<TObj*>& arr, TObj* obj)
	{
		arr << obj;
	}

	//惑星オブジェクトの追加を行う
	void ObjectGroup::addPlanet(Planet* planet)
	{
		add(planets_, planet);
	}

	//艦隊オブジェクトの追加を行う
	void ObjectGroup::addShip(Ship* ship)
	{
		add(ships_, ship);
	}

	void ObjectGroup::addShot(Shot* shot)
	{
		add(shots_, shot);
	}

	//記録されたオブジェクトを参照する
	template <class TObj>
	TObj* ObjectGroup::get(Array<TObj*>& arr, int32 n)
	{
		return arr[n];
	}

	//記録された惑星オブジェクトを参照する
	Planet* ObjectGroup::getPlanet(int32 n)
	{
		return get(planets_, n);
	}

	//記録された艦隊オブジェクトを参照する
	Ship* ObjectGroup::getShip(int32 n)
	{
		return get(ships_, n);
	}

	Shot* ObjectGroup::getShot(int32 n)
	{
		return get(shots_, n);
	}

	void ObjectGroup::deleteShot(int32 n)
	{
		shots_.remove_at(n);
		delete(shots_[n]);
	}

	void ObjectGroup::deleteShot(Shot* shot)
	{
		shots_.remove(shot);
		delete(shot);
	}

	Array<Shot*> ObjectGroup::getShotByArray()
	{
		return shots_;
	}

	Array<Ship*> ObjectGroup::getShipFriend()
	{
		Array<Ship*> result;
		for (auto i : step(ships_.size()))
			if (ships_[i]->getSide() == Side::Friend)
				result << ships_[i];
		return result;
	}

	Array<Ship*> ObjectGroup::getShipHostile()
	{
		Array<Ship*> result;
		for (auto i : step(ships_.size()))
			if (ships_[i]->getSide() == Side::Hostile)
				result << ships_[i];
		return result;
	}

	Array<Ship*> ObjectGroup::getShipNeutral()
	{
		Array<Ship*> result;
		for (auto i : step(ships_.size()))
			if (ships_[i]->getSide() == Side::Neutral)
				result << ships_[i];
		return result;
	}

	//初期惑星オブジェクトを参照する
	Planet ObjectGroup::getInitPlanet()
	{
		return *planetInit_;
	}

	int32 ObjectGroup::sizePlanet()
	{
		return planets_.size();
	}

	int32 ObjectGroup::sizeShip()
	{
		return ships_.size();
	}

	int32 ObjectGroup::sizeShot()
	{
		return shots_.size();
	}

	//初期味方惑星オブジェクトを生成する
	void ObjectGroup::initPlanet()
	{
		planetInit_ = new Planet(RandomPoint(Rect{ 0, 0, VALID_WIDTH, VALID_HEIGHT }),
			PLANET_SCALE, PLANET_DEFAULT_HP, PLANET_DEFAULT_SHIELD, PLANET_CRANGE, INIT_PLANET_KEY,
			Side::Friend, Shield::Type::Lv1R);
		addPlanet(planetInit_);
	}

	//ランダムにn個の敵惑星オブジェクトを生成する
	void ObjectGroup::addPlanetRandom(int32 n)
	{
		Vec2 pos;				//乱数座標計算用
		int32 tem;				//一時カウント用
		int32 limit = 0;		//探索限度
		bool reject = false;	//オブジェクト棄却
		String key;

		for (auto i : step(n))
		{
			{
				//アセットキーをランダムで選択
				Array<String> arr;

				//Planetタグの入ったキーを文字列リストとして取り出す
				for (auto [key, asset] : GlobalVar::assetHash)
					if (asset.tag_.contains(U"Planet"))
						arr << key;

				//文字列リストからランダムにキーを取り出す
				key = Sample(arr);
			}

			//棄却スイッチを初期化
			reject = false;

			while(true)
			{
				//カウントを初期化
				tem = 0;

				//乱数座標を取得
				pos = RandomVec2(RectF{ 0, 0, VALID_WIDTH, VALID_HEIGHT });

				//惑星どうしの重なりがないかどうか判定

				//現在存在する惑星が０ならば座標を確定
				if (planets_.size() == 0)
					break;

				//惑星の位置から円形上の範囲を適用　それに重なっていれば座標を計算しなおす
				for (auto i : step(planets_.size()))
				{
					//距離が規定星間距離を満たしていなかった場合　座標の計算しなおし
					if (Distance(planets_[i]->xy_(), pos) < TextureAsset(key).width() * PLANET_DISTANCE)
						break;
					tem++;
				}

				//乱数による計算繰り返し限度を超えた場合
				if (limit > POS_RAND_LIMIT)
				{
					reject = true;
					break;
				}

				//ループが最後まで回ったか否か
				if (tem >= planets_.size())
					//回ったなら重なりはない　座標を確定
				{
					limit = 0;
					break;
				}
				else
					//回っていないなら重なっていない　座標を計算しなおす
				{
					limit++;
					continue;
				}
			}

			//惑星を追加
			if (reject == false)
				addPlanet(new Planet{ pos, PLANET_SCALE, 100, PLANET_CRANGE, key, Side::Hostile});
			else
				break;
		}
	}

	ObjectGroup ObjectGroup::chkAreaCR(ObjectParam* obj)
	{
		//結果グループオブジェクト
		ObjectGroup result;

		//指定オブジェクトの可認知範囲に惑星オブジェクトの当たり判定が入っていれば結果に追加
		for (auto i : step(GlobalVar::group.sizePlanet()))
			//指定オブジェクト自身は除外
			if (GlobalVar::group.getPlanet(i) != obj &&
				Circle{ obj->xy_(), obj->crange_ }.intersects(GlobalVar::group.getPlanet(i)->getCD()))
				result.addPlanet(GlobalVar::group.getPlanet(i));

		//指定オブジェクトの可認知範囲に艦隊オブジェクトの当たり判定が入っていれば結果に追加
		for (auto i : step(GlobalVar::group.sizeShip()))
			//指定オブジェクト自身は除外
			if (GlobalVar::group.getShip(i) != obj &&
				Circle{ obj->xy_(), obj->crange_ }.intersects(GlobalVar::group.getShip(i)->getCD()))
				result.addShip(GlobalVar::group.getShip(i));

		return result;
	}

	ObjectGroup ObjectGroup::chkHostileSelf(ObjectSide* obj)
	{
		//結果グループオブジェクト
		ObjectGroup result;

		//オブジェクト群のうち惑星オブジェクト
		for (auto i : step(planets_.size()))
			//指定オブジェクトと敵対関係か
			if (obj->chkHostileSelf(*planets_[i]))
				result.addPlanet(planets_[i]);

		//オブジェクト群のうち艦隊オブジェクト
		for (auto i : step(ships_.size()))
			//指定オブジェクトと敵対関係か
			if (obj->chkHostileSelf(*ships_[i]))
				result.addShip(ships_[i]);

		return result;
	}

	Array<Shot*> ObjectGroup::getTouchShot(ObjectEllipseCD* obj)
	{
		//弾オブジェクトをリスト形式で取得する
		Array<Shot*> shots = GlobalVar::group.getShotByArray();

		//結果リスト
		Array<Shot*> result;

		//当たり判定に弾オブジェクトが接触しているか探索
		for (auto it = shots.begin(); it != shots.end();)
		{
			//イテレータをポインタに変換
			Shot* tmp = *it;

			//弾が当たり判定に接触していたら
			if (obj->getCD().intersects(tmp->getCD()))
				result << tmp;

			//イテレータを進める
			++it;
		}

		return result;
	}
}
