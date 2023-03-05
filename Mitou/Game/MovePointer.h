#pragma once

namespace SpaceWar
{
	class MovePointer : public Object
	{
	public:

		//public変数宣言

		bool active_;

		//public関数宣言

		//コンストラクタ
		MovePointer();
		MovePointer(double, double);
		MovePointer(Vec2);

		//更新を行う
		void update();
	};
}

