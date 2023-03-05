#include "stdafx.h"

namespace SpaceWar
{
	SelectRect::SelectRect(ColorF color, ColorF colorFrame) : color_(color), colorFrame_(colorFrame),
		active_(true), sp_(0.0, 0.0), ep_(0.0, 0.0), rect_(sp_, ep_)
	{

	}

	void SelectRect::update()
	{
		//描画処理はアクティブ時に行う
		if (active_)
		{
			//押した瞬間の座標を始点とする
			if (MouseL.down())
				sp_ = Cursor::Pos();

			//押している間矩形を表示
			if (MouseL.pressed())
			{
				//マウスカーソルの位置を終点とする
				ep_ = Cursor::Pos();
				//始点と終点から選択範囲矩形を作成する
				rect_ = RectF{ sp_, ep_ - sp_ };
				rect_.draw(color_);
				rect_.drawFrame(0.5, 0.5, colorFrame_);
			}

			//離した瞬間アクティブ状態にある味方艦隊があれば左クリック機能を切り替え
			if (MouseL.up())
			{
				//矩形の形状を初期化する
				rect_ = RectF{ 0.0, 0.0 };

				//全味方艦隊を取得
				Array<Ship*> ships = GlobalVar::group.getShipFriend();

				//アクティブ状態にある味方艦隊があるかどうか
				for (auto i : step(ships.size()))
					if (ships[i]->active_)
					{
						//アクティブ状態を切り替え
						active_ = false;
						GlobalVar::mpointer.active_ = true;
					}
			}

			//右クリックを押したらすべてのオブジェクトのアクティブ状態を解除する
			if (MouseR.down())
				for(auto i : step(GlobalVar::group.sizeShip()))
					GlobalVar::group.getShip(i)->active_ = false;

			//選択範囲内にオブジェクトがあればアクティブ状態にする
			for (auto i : step(GlobalVar::group.sizeShip()))
				if (isArea(GlobalVar::group.getShip(i)))
					GlobalVar::group.getShip(i)->active_ = true;
		}
	}

	Vec2 SelectRect::getCenter()
	{
		return rect_.center();
	}

	Vec2 SelectRect::getLeftUpper()
	{
		return getCenter() - getArea() / 2;
	}

	Vec2 SelectRect::getArea()
	{
		return Vec2{ Math::Abs(sp_ - ep_) };
	}


	bool SelectRect::isArea(Vec2 xy)
	{
		return rect_.intersects(xy);
	}

	bool SelectRect::isArea(ObjectEllipseCD* obj)
	{
		return RectF{ getLeftUpper(), getArea() }.intersects(obj->getCD());
	}
}
