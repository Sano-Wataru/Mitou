#pragma once

namespace SpaceWar
{
	class ParentTable
	{
	private:

		//private変数宣言

		HashTable<Gun*, Ship*> hashGS_;
		HashTable<Shot*, Gun*> hashSG_;

	public:

		//public関数宣言

		ParentTable();

		//指定したオブジェクトに対応する親艦隊オブジェクトを返す
		Ship* getShip(Shot*);
		Ship* getShip(Gun*);
		//指定したオブジェクトに対応する親銃オブジェクトを返す
		Gun* getGun(Shot*);
		//要素１を子として要素２のオブジェクトを追加する
		void add(Gun*, Ship*);
		void add(Shot*, Gun*);
	};
}

