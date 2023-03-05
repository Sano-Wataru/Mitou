#pragma once

namespace SpaceWar
{
	class AssetSym
	{
	public:
		String key_;
		String path_;
		HashSet<String> tag_;

		AssetSym();
		AssetSym(String, String, HashSet<String>);
	};
}
