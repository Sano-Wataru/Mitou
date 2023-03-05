#include "stdafx.h"

namespace SpaceWar
{
	MovePointer::MovePointer() : MovePointer(0.0, 0.0)
	{

	}

	MovePointer::MovePointer(double x, double y) : Object(x, y), active_(false)
	{

	}

	MovePointer::MovePointer(Vec2 xy) : MovePointer(xy.x, xy.y)
	{

	}

	void MovePointer::update()
	{
		//アクティブ時描画処理を行う
		if (active_)
		{
			//マウス押下時にポインタをマウスカーソルに合わせて描画
			if (MouseL.pressed())
			{
				//ポインタ座標更新
				xy_(Cursor::Pos());

				//ポインタ描画
				Circle{ xy_(), 30}.draw();
			}

			//左クリックを離した、あるいは右クリック時に左クリック操作を切り替え
			if (MouseL.up() || MouseR.down())
			{
				//アクティブ状態を切り替え
				active_ = false;
				GlobalVar::select.active_ = true;

				//左クリックを離した際には味方艦隊オブジェクトの移動を行う
				if (MouseL.up())
				{
					//味方艦隊オブジェクトの移動目標座標を現在の移動ポインタの位置に

					//全味方艦隊オブジェクト取得
					Array<Ship*> ships = GlobalVar::group.getShipFriend();

					//全味方艦隊オブジェクトのうちアクティブ状態のものを目的座標へ移動させる
					for (auto i : step(ships.size()))
						if (ships[i]->active_)
							ships[i]->setTargetPos(xy_());
				}
				
				//全オブジェクトのアクティブ状態をオフに
				for (auto i : step(GlobalVar::group.sizeShip()))
					GlobalVar::group.getShip(i)->active_ = false;

				for (auto i : step(GlobalVar::group.sizePlanet()))
					GlobalVar::group.getPlanet(i)->active_ = false;
			}
		}
	}
}
