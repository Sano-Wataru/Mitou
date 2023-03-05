#pragma once

namespace SpaceWar
{
	class StopwatchA
	{
	private:

		//private変数宣言

		Stopwatch* stopwatch_;

	public:

		//public関数宣言

		StopwatchA();

		//ストップウォッチが指定した秒数以上になったときにtrueを返す
		bool watchState(double);
	};
}

