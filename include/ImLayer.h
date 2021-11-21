#pragma once
#include <string>

#define EngineExport  __declspec( dllexport )

namespace Oyun
{
	namespace Imgui
	{
		class EngineExport ImLayer
		{
		public:
			std::string name;

			ImLayer(const std::string rName)
				:name{rName}
			{
			};

			virtual void Draw() = 0;
		};
	}
}