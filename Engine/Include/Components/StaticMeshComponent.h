#ifndef OYUN_STATIC_MESH_COMPONENT_H__
#define OYUN_STATIC_MESH_COMPONENT_H__

#include "components/Component.h"
#include "ModelStore.h"
namespace Oyun
{
	class Entity;
	class Model;
	class OYUN_API StaticMeshComponent : public Component
	{
	public:
		StaticMeshComponent(Entity*, Model*);

		void Draw(float* view, float* proj, float* transform, Window* wnd);


		// Inherited via Component
		virtual Jsones::JObj* ConvertToJson() override;

		// Inherited via Component
		virtual void DrawAtEditorProps() override;

	private:
		Model* mModel;






	};
}

#endif //OYUN_STATIC_MESH_COMPONENT_H__