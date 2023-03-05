#pragma once

namespace SpaceWar
{
	class ObjectGroup
	{
	private:

		//privateメンバ変数宣言

		//惑星オブジェクト群管理用
		Array<Planet*> planets_;
		//艦隊オブジェクト群管理用
		Array<Ship*> ships_;
		//弾オブジェクト群管理用
		Array<Shot*> shots_;
		//初期惑星オブジェクト
		Planet* planetInit_;

		//privateメンバ関数宣言

		//オブジェクトの追加を行う
		template <class TObj>
		void add(Array<TObj*>&, TObj*);

		//指定した要素のオブジェクトを取得する
		template <class TObj>
		TObj* get(Array<TObj*>&, int32 n);

	public:
		
		//publicメンバ関数宣言
		ObjectGroup();

		//更新を行う
		void update();

		//惑星オブジェクトの追加を行う
		void addPlanet(Planet*);
		//艦隊オブジェクトの追加を行う
		void addShip(Ship*);
		//弾オブジェクトの追加を行う
		void addShot(Shot*);

		//指定した要素の惑星オブジェクトを取得する
		Planet* getPlanet(int32);
		//指定した要素の艦隊オブジェクトを取得する
		Ship* getShip(int32);
		//指定した要素の弾オブジェクトを取得する
		Shot* getShot(int32);
		//弾オブジェクトのリストを取得する
		Array<Shot*> getShotByArray();

		//指定した要素を弾オブジェクトリストから削除する
		void deleteShot(int32);
		//指定したアドレスを弾オブジェクトリストから削除する
		void deleteShot(Shot*);

		//味方艦隊オブジェクトをリスト形式で取得する
		Array<Ship*> getShipFriend();
		//敵対艦隊オブジェクトをリスト形式で取得する
		Array<Ship*> getShipHostile();
		//中立艦隊オブジェクトをリスト形式で取得する
		Array<Ship*> getShipNeutral();

		//惑星オブジェクトのサイズを取得する
		int32 sizePlanet();
		//艦隊オブジェクトのサイズを取得する
		int32 sizeShip();
		//弾オブジェクトのサイズを取得する
		int32 sizeShot();
		
		//初期惑星を取得する
		Planet getInitPlanet();

		//初期惑星の追加を行う
		void initPlanet();
		//ランダムパラメータの最大n個の惑星オブジェクトを追加する
		void addPlanetRandom(int32);

		//可認知範囲のオブジェクトをオブジェクト群形式で返す
		ObjectGroup chkAreaCR(ObjectParam*);
		//自身と敵対するオブジェクトをオブジェクト群形式で返す
		ObjectGroup chkHostileSelf(ObjectSide*);
		//指定したオブジェクトの当たり判定に接触した弾オブジェクトを返す　接触していなければnull
		Array<Shot*> getTouchShot(ObjectEllipseCD*);
	};
}

