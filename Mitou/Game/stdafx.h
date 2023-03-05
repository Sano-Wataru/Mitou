# pragma once

#include <Siv3D.hpp>
#include "GameEffect.h"
#include "StopwatchA.h"
#include "enums.h"
#include "Pos3.h"
#include "AssetSym.h"
#include "consts.h"

#include "BackGround.h"
#include "Object.h"
#include "ObjectPic.h"
#include "ObjectEllipseCD.h"
#include "ObjectSide.h"
#include "Shield.h"
#include "Shot.h"
#include "Gun.h"
#include "ObjectParam.h"
#include "Gauge.h"
#include "ObjectRectCD.h"
#include "Planet.h"
#include "Ship.h"

#include "ParentTable.h"
#include "SelectRect.h"
#include "MovePointer.h"

#include "ObjectGroup.h"

#include "Map.h"

namespace SpaceWar
{
	namespace GlobalVar
	{
		//エフェクトオブジェクト
		inline Effect* effect;

		//選択範囲オブジェクト作成
		inline SelectRect select;

		//移動ポインタオブジェクト作成
		inline MovePointer mpointer;

		//背景オブジェクト作成
		inline BackGround background;

		//オブジェクト群作成
		inline ObjectGroup group;

		//アセット名とパスの組
		inline HashTable<String, AssetSym> assetHash =
		{
			{ U"Planet1", { U"Planet1", U"pictures/star/star1.png", { U"Planet"} } },
			{ U"Planet2", { U"Planet2", U"pictures/star/star2.png", { U"Planet"} } },
			{ U"Planet3", { U"Planet3", U"pictures/star/star3.png", { U"Planet" } } },
			{ U"Planet4", { U"Planet4", U"pictures/star/star4.png", { U"Planet" } } },
			{ U"Planet5", { U"Planet5", U"pictures/star/star5.png", { U"Planet" } } },
			{ U"Planet6", { U"Planet6", U"pictures/star/star6.png", { U"Planet" } } },
			{ U"Planet7", { U"Planet7", U"pictures/star/star7.png", { U"Planet" } } },
			{ U"Planet8", { U"Planet8", U"pictures/star/star8.png", { U"Planet" } } },
			{ U"Planet9", { U"Planet9", U"pictures/star/star9.png", { U"Planet" } } },
			{ U"Ship1", { U"Ship1", U"pictures/ship/ship1.png", { U"Ship" } } },
			{ U"Ship2", { U"Ship2", U"pictures/ship/ship2.png", { U"Ship" } } },
			{ U"Ship3", { U"Ship3", U"pictures/ship/ship3.png", { U"Ship" } } },
			{ U"Ship4", { U"Ship4", U"pictures/ship/ship4.png", { U"Ship" } } },
			{ U"Ship5", { U"Ship5", U"pictures/ship/ship5.png", { U"Ship" } } },
			{ U"Shot1", { U"Shot1", U"pictures/shot/shot1.png", { U"Shot" } } },
			{ U"Shot2", { U"Shot2", U"pictures/shot/shot2.png", { U"Shot" } } },
			{ U"Shield1", { U"Shield", U"pictures/other/shield1.png", { U"Shield" } } },
			{ U"ShieldR1", { U"ShieldR", U"pictures/other/shieldR1.png", { U"ShieldR" } } },
			{ U"Shield2", { U"Shield", U"pictures/other/shield2.png", { U"Shield" } } },
			{ U"ShieldR2", { U"ShieldR", U"pictures/other/shieldR2.png", { U"ShieldR" } } },
			{ U"Shield3", { U"Shield", U"pictures/other/shield3.png", { U"Shield" } } },
			{ U"ShieldR3", { U"ShieldR", U"pictures/other/shieldR3.png", { U"ShieldR" } } }
		};

		//アセットと色の組（エフェクト用）
		inline HashTable<String, ColorF> shotColor =
		{
			{ U"Shot1", Palette::Red },
			{ U"Shot2", Palette::Deepskyblue}
		};

		//オブジェクトの親子関係を示すハッシュテーブル
		inline ParentTable parentTable;

		//2Dカメラ作成
		inline Camera2D camera;

		//マップオブジェクト作成
		inline Map map;

		//当たり判定を可視化する
		inline bool visibleCD = false;

		//可認知範囲を可視化する
		inline bool visibleCR = false;
	}

	//二次元ベクトルの和を求める関数
	double Sum(Vec2);
	//二座標の距離を求める関数
	double Distance(Vec2, Vec2);

	//二つの座標の偏角を返す関数
	double Atan2(Vec2, Vec2);
	double Atan2_deg(Vec2, Vec2);

	//始点・終点のxy増加量を求め、その比を-1～1に正規化する
	Vec2 incRatio(Vec2, Vec2);

	//ある角度からある角度までの線形補間を求める
	double lerpAngle(double, double, double);

	//指定オブジェクトに一番近いオブジェクトをオブジェクト群から一つ選び出す
	Object* nearest(Object, ObjectGroup);

	namespace Operation
	{
		//艦隊JSONデータからオブジェクトを追加する
		void addShip(String, Vec2, double = 0.0, Side = Side::Friend,
			Shield::Type = Shield::Type::Lv1);
	}
	
}
