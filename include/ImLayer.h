#ifndef OYUN_IMLAYER_H__
#define OYUN_IMLAYER_H__

#include <string>

#ifdef OyunEngine_EXPORTS
#define OYUN_API __declspec(dllexport)
#else
#define OYUN_API __declspec(dllimport)
#endif

namespace Oyun
{
	namespace Imgui
	{
		class OYUN_API ImLayer
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

#endif //OYUN_IMLAYER_H__