#ifndef OYUN_COMPONENT_H__
#define OYUN_COMPONENT_H__

#ifdef OyunEngine_EXPORTS
#define OYUN_API __declspec(dllexport)
#else
#define OYUN_API __declspec(dllimport)
#endif

namespace Jsones
{
	struct JObj;
}

namespace Oyun
{
	class Entity;

	class OYUN_API Component
	{
	public:
		Component(Entity*);
		~Component();

		virtual void BeginPlay();
		virtual void EndPlay();

		virtual void DrawAtEditorProps() = 0;
		virtual Jsones::JObj* ConvertToJson() = 0;


	protected :
		Entity* mEntity;
	};
}

#endif //OYUN_COMPONENT_H__
