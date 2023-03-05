#include "stdafx.h"

namespace SpaceWar
{
	double Sum(Vec2 v)
	{
		return v.x + v.y;
	}

	double Distance(Vec2 v1, Vec2 v2)
	{
		return Sqrt(Sum(Pow(v1 - v2, 2)));
	}

	double Atan2(Vec2 pos1, Vec2 pos2)
	{
		double result = Math::Atan2(pos2.y - pos1.y, pos2.x - pos1.x);
		if (result < 0)
			result += Math::TwoPi;
		return result;
	}

	double Atan2_deg(Vec2 pos1, Vec2 pos2)
	{
		return ToDegrees(Atan2(pos1, pos2));
	}

	Vec2 incRatio(Vec2 pos1, Vec2 pos2)
	{
		Vec2 diff = pos2 - pos1;
		double max = Max(Abs(diff.x), Abs(diff.y));

		return diff / max;
	}

	double lerpAngle(double from, double to, double ratio)
	{
		double diff = to - from;
		if (Abs(diff) > 180)
			if (diff >= 0)
				return (diff - 360) * ratio;
			else
				return (diff + 360) * ratio;
		else
			return diff * ratio;
	}

	Object* nearest(Object obj, ObjectGroup group)
	{
		double min;
		Object* mobj = nullptr;

		//惑星オブジェクトと比較
		for (auto i : step(group.sizePlanet()))
			//現在の最小値よりも計算結果が小さかったら結果を更新
			if (i == 0 || min > Distance(obj.xy_(), group.getPlanet(i)->xy_()))
			{
				mobj = group.getPlanet(i);
				min = Distance(obj.xy_(), mobj->xy_());
			}

		//艦隊オブジェクトと比較
		for (auto i : step(group.sizeShip()))
			//現在の最小値よりも計算結果が小さかったら結果を更新
			if (i == 0 || min > Distance(obj.xy_(), group.getShip(i)->xy_()))
			{
				mobj = group.getShip(i);
				min = Distance(obj.xy_(), mobj->xy_());
			}

		return mobj;
	}

	namespace Operation
	{
		void addShip(String key, Vec2 xy, double angle, Side side, Shield::Type type)
		{
			//艦隊のJSONオブジェクト
			JSON shipJson = SHIP_JSON[key];

			//追加する艦隊オブジェクトを作成
			Ship* ship = new Ship{ xy, angle, shipJson[U"hp"].get<double>(), shipJson[U"shield"].get<double>(),
				shipJson[U"speed"].get<double>(), shipJson[U"crange"].get<double>(), shipJson[U"key"].getString(),
				side, type};

			//艦隊オブジェクトのアドレスを追加
			GlobalVar::group.addShip(ship);

			//銃追加処理は以下
			String gun = SHIP_JSON[key][U"gun"].getString();

			if (gun != U"")
			{
				//銃のJSONオブジェクト
				JSON gunJson = GUN_JSON[gun];

				for (auto i : step(gunJson[U"ox"].size()))
				{
					//銃オブジェクトを追加
					ship->addGun(gunJson[U"ox"][i].get<double>(), gunJson[U"oy"][i].get<double>(),
						gunJson[U"damage"][i].get<double>(), gunJson[U"interval"][i].get<double>(),
						gunJson[U"speed"][i].get<double>(), gunJson[U"duration"][i].get<double>(),
						gunJson[U"key"][i].getString());
				}
			}
		}
	}
}
