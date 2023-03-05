#include "stdafx.h"

namespace SpaceWar
{
	ObjectPic::ObjectPic(double x, double y, double scale, double angle, String key) :
		Object(x, y), scale_(scale), angle_(angle), asset_(GlobalVar::assetHash[key]), texture_(TextureAsset(key))
	{

	}
}
