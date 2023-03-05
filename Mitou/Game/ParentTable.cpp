#include "stdafx.h"

namespace SpaceWar
{
	ParentTable::ParentTable()
	{

	}

	Ship* ParentTable::getShip(Shot* shot)
	{
		return hashGS_[hashSG_[shot]];
	}

	Ship* ParentTable::getShip(Gun* gun)
	{
		return hashGS_[gun];
	}

	Gun* ParentTable::getGun(Shot* shot)
	{
		return hashSG_[shot];
	}

	void ParentTable::add(Gun* gun, Ship* ship)
	{
		//指定した子が既に登録されているならば削除する
		if (hashGS_.contains(gun))
			hashGS_.erase(gun);

		//登録
		hashGS_.emplace(gun, ship);
	}

	void ParentTable::add(Shot* shot, Gun* gun)
	{
		//指定した子が既に登録されているならば削除する
		if (hashSG_.contains(shot))
			hashSG_.erase(shot);

		//登録
		hashSG_.emplace(shot, gun);
	}
}
