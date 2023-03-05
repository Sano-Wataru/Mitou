#include "stdafx.h"

void Main()
{
	using namespace SpaceWar;

	//ウィンドウサイズ設定
	Window::Resize(WINDOW_WIDTH, WINDOW_HEIGHT);
	//画像ファイルのアセット読み込みおよび登録
	for (auto [key, asset] : GlobalVar::assetHash)
		TextureAsset::Register(key, asset.path_, TextureDesc::Mipped);

	//エフェクトオブジェクト作成
	GlobalVar::effect = new Effect;

	//初期惑星作成
	GlobalVar::group.initPlanet();

	//カメラ基準座標
	Vec2 baseXY = { VALID_WIDTH / 2, VALID_HEIGHT / 2 };
	//2Dカメラ作成
	GlobalVar::camera = Camera2D{ GlobalVar::group.getInitPlanet().xy_(), 1.0, CameraControl::Keyboard };

	//敵惑星をランダム配置
	GlobalVar::group.addPlanetRandom(10);

	Operation::addShip(U"ship2_std", GlobalVar::group.getInitPlanet().xy_(), 0.0);
	Operation::addShip(U"ship1_std", GlobalVar::group.getInitPlanet().xy_() + Point{ 100, 100 }, 0.0);
	Operation::addShip(U"ship1_std", GlobalVar::group.getInitPlanet().xy_() + Point{ 200, 200 }, 0.0,
		Side::Hostile);
	Operation::addShip(U"ship2_std", GlobalVar::group.getInitPlanet().xy_() + Point{ 200, 250 }, 0.0,
		Side::Hostile);

	//マップオブジェクト作成
	GlobalVar::map = Map{ Window::GetState().virtualSize.xy() - Point{ MAP_WIDTH + 20 , MAP_HEIGHT + 20 } };

	while (System::Update())
	{
		ClearPrint();

		//2Dカメラ更新
		GlobalVar::camera.update();
		{
			{
				//背景用レンダー
				const Transformer2D tBack(Mat3x2::Translate((baseXY -
					GlobalVar::camera.getCenter()) * STAR_FLOW_SPEED));
		
				//背景更新
				GlobalVar::background.update();
			}

			//2Dカメラの設定からTransformer2Dを作成
			const auto tCamera = GlobalVar::camera.createTransformer();

			//オブジェクト群更新
			GlobalVar::group.update();

			//移動ポインタオブジェクト更新
			GlobalVar::mpointer.update();

			//選択範囲オブジェクト更新
			GlobalVar::select.update();

			//エフェクトオブジェクト更新
			GlobalVar::effect->update();
		}

		//ミニマップ更新
		GlobalVar::map.update();

		SimpleGUI::CheckBox(GlobalVar::visibleCD, U"visibleCD", Vec2{ 650, 10 });
		SimpleGUI::CheckBox(GlobalVar::visibleCR, U"visibleCR", Vec2{ 650, 40 });

		//範囲外に出たカメラを初期惑星に戻す
		if (not GlobalVar::camera.getCenter().intersects(Rect{ 0, 0, VALID_WIDTH, VALID_HEIGHT }))
		{
			GlobalVar::camera.setTargetCenter(Vec2{GlobalVar::group.getInitPlanet().xy_()});
		}
	}
}
