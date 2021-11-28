#ifndef OYUN_COMPONENT_H__
#define OYUN_COMPONENT_H__

#define EngineExport   __declspec( dllexport )

namespace Oyun
{
	class EngineExport Component
	{
	public:
		Component();
		~Component();

		virtual void BeginPlay();
		virtual void EndPlay();

	};
}

#endif //OYUN_COMPONENT_H__
