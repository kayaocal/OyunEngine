#ifndef OYUN_COMPONENT_H__
#define OYUN_COMPONENT_H__

#define EngineExport   __declspec( dllexport )

namespace Oyun
{
	class EngineExport Component
	{
	public:
		Component(const char* cName);
		~Component();

		const char* name;

		const char* GetComponentName() const;

		virtual void BeginPlay() = 0;
		virtual void EndPlay() = 0;

	};
}

#endif //OYUN_COMPONENT_H__
