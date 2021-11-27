#pragma once

#include "ImLayer.h"

namespace Oyun
{
	class Camera;
}

namespace Editor
{

	class EditorDockableWindowLayer : public Oyun::Imgui::ImLayer
	{
	public:


		EditorDockableWindowLayer(const std::string rName);

		virtual void Draw();

		void DrawDockableWindow();
		void DrawMenuBar();
		void DrawViewPort();
	};

	class EditorPropertiesLayer : public Oyun::Imgui::ImLayer
	{
	public:
		EditorPropertiesLayer(const std::string rName);

		virtual void Draw();
	};

	class EditorSceneLayer : public Oyun::Imgui::ImLayer
	{
	public:
		EditorSceneLayer(const std::string rName);

		virtual void Draw();
	};

	class EditorViewPortLayer : public Oyun::Imgui::ImLayer
	{
	public:

		EditorViewPortLayer(const std::string rName, Oyun::Camera* cam);

		virtual void Draw();

	private:
		Oyun::Camera* defaultCamera;
		bool mShowStats;
	};
}