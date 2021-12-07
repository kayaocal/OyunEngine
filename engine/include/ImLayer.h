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
	struct Engine;

	namespace Imgui
	{
		class OYUN_API ImLayer
		{
		public:
			std::string name;


			ImLayer(const std::string rName, Engine* engine)
				:name{rName}, mEngine(engine)
			{
			};

			virtual void Draw() = 0;

		protected:
			Engine* mEngine;	
		};
	}
}

#endif //OYUN_IMLAYER_H__