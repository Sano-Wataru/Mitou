#pragma once

namespace SpaceWar
{
	//ウィンドウサイズ

	//ウィンドウ幅
	const int32 WINDOW_WIDTH = 800;
	//ウィンドウ高さ
	const int32 WINDOW_HEIGHT = 600;

	//有効ステージサイズ

	//ステージ幅
	const int32 VALID_WIDTH = 4000;
	//ステージ高さ
	const int32 VALID_HEIGHT = 4000;

	//背景情報

	//星密度
	const double STAR_AMOUNT = 0.005;
	//星の流れる速度
	const double STAR_FLOW_SPEED = 0.05;

	//惑星間距離デフォルト
	const double PLANET_DISTANCE = 2.0;
	//座標乱数繰り返し限度
	const double POS_RAND_LIMIT = 100.0;

	//オブジェクト情報

	//初期味方惑星アセット
	const String INIT_PLANET_KEY = U"Planet1";
	//惑星デフォルトHP値
	const double PLANET_DEFAULT_HP = 100.0;
	//惑星デフォルトシールド値
	const double PLANET_DEFAULT_SHIELD = 100.0;

	//艦隊デフォルトHP値
	const double SHIP_DEFAULT_HP = 100.0;
	//艦隊デフォルトSHIELD値
	const double SHIP_DEFAULT_SHIELD = 100.0;
	//艦隊デフォルトSPEED値
	const double SHIP_DEFAULT_SPEED = 1.0;

	//ミニマップ情報

	//ミニマップ幅
	const int32 MAP_WIDTH = 100;
	//ミニマップ高さ
	const int32 MAP_HEIGHT = 100;


	//選択範囲デフォルト色
	const ColorF SRC_DEFAULT = { 0.25, 0.5, 1.0, 0.25 };
	//選択範囲デフォルトフレーム色
	const ColorF SRC_DEFAULT_FRAME = { 0.25, 0.5, 1.0 };


	//惑星縮尺
	const double PLANET_SCALE = 0.6;
	//艦隊縮尺
	const double SHIP_SCALE = 0.2;
	//弾縮尺
	const double SHOT_SCALE = 0.1;
	//シールド縮尺
	const double PLANET_SHIELD_SCALE = 1.1;
	const double SHIP_SHIELD_SCALE = 0.4;


	//惑星デフォルト可認知範囲
	const double PLANET_CRANGE = 800.0;
	//艦隊デフォルト可認知範囲
	const double SHIP_CRANGE = 250.0;

	//各種ゲージ色

	//HPゲージ色
	const Color COLOR_HP_GAUGE = { 255, 150, 0 };
	//シールドゲージ色
	const Color COLOR_SHIELD_GAUGE = { 0, 150, 255 };
	//Rシールドゲージ色
	const Color COLOR_RSHIELD_GAUGE = { 60, 0, 255 };
	//シールド破片色
	const Color COLOR_FRAGMENT_LV1 = { 50, 140, 235, 180 };
	const Color COLOR_FRAGMENT_LV2 = { 180, 0, 190, 180 };
	const Color COLOR_FRAGMENT_LV3 = { 200, 15, 70, 180 };

	//艦隊JSONデータ
	const JSON SHIP_JSON = JSON::Load(U"data/shipData.json");
	const JSON GUN_JSON = JSON::Load(U"data/gunData.json");
}
