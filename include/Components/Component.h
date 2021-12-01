#ifndef OYUN_COMPONENT_H__
#define OYUN_COMPONENT_H__

#ifdef OyunEngine_EXPORTS
#define OYUN_API __declspec(dllexport)
#else
#define OYUN_API __declspec(dllimport)
#endif

namespace Oyun
{
	class OYUN_API Component
	{
	public:
		Component();
		~Component();

		virtual void BeginPlay();
		virtual void EndPlay();

	};
}

#endif //OYUN_COMPONENT_H__
