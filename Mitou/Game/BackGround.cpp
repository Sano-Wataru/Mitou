#include "stdafx.h"

namespace SpaceWar
{
	BackGround::BackGround() : width_(VALID_WIDTH), height_(VALID_HEIGHT),
							   sNum_(STAR_AMOUNT *
								   (WINDOW_WIDTH + STAR_FLOW_SPEED * VALID_WIDTH) *
								   (WINDOW_HEIGHT + STAR_FLOW_SPEED * VALID_HEIGHT))
	{
		//背景の星を描画するためのリストを作成
		for (auto i : step(sNum_))
			stars_ << Circle{ RandomVec2(
				RectF{ Arg::center(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2),
				WINDOW_WIDTH + STAR_FLOW_SPEED * VALID_WIDTH, WINDOW_HEIGHT + STAR_FLOW_SPEED * VALID_HEIGHT }),
				Random<double>(0, 1)};
	}

	void BackGround::update()
	{
		//星を描画
		for (auto i : step(sNum_))
			stars_[i].draw();
	}
}
