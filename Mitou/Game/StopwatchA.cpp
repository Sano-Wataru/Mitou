#include "stdafx.h"

namespace SpaceWar
{
	StopwatchA::StopwatchA() : stopwatch_(nullptr)
	{

	}

	bool StopwatchA::watchState(double sec)
	{
		//ストップウォッチが始まっていなければ
		if (stopwatch_ == nullptr)
			stopwatch_ = new Stopwatch(StartImmediately::Yes);
		else
			//ストップウォッチが動作中ならば
			if (stopwatch_->isStarted())
				//指定した秒数を上回ったら
				if (stopwatch_->sF() >= sec)
				{
					//ストップウォッチを削除しtrueを返す
					stopwatch_ = nullptr;
					return true;
				}

		//上記以外はすべてfalse
		return false;
	}
}
