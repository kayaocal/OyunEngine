#include "EditorImLayer.h"
#include "imgui.h"
#include "Camera.h"
#include <iostream>
#include <string>
#include <Engine.h>
namespace Editor
{
    EditorDockableWindowLayer::EditorDockableWindowLayer(const std::string rName)
        :Oyun::Imgui::ImLayer(rName)
    {
    }

    void EditorDockableWindowLayer::Draw()
    {
        DrawDockableWindow();
    }

    void EditorDockableWindowLayer::DrawDockableWindow()
    {
        bool p_open = true;
        static bool opt_fullscreen = true;
        static bool opt_padding = false;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }
        else
        {
            dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
        }

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
        // and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        if (!opt_padding)
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin(name.c_str(), &p_open, window_flags);
        if (!opt_padding)
            ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // Submit the DockSpace
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }
        DrawMenuBar();

        ImGui::End();


    }

    void EditorDockableWindowLayer::DrawMenuBar()
    {
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Open")) {}
                if (ImGui::BeginMenu("Open Recent"))
                {
                    ImGui::MenuItem("fish_hat.c");
                    ImGui::MenuItem("fish_hat.inl");
                    ImGui::MenuItem("fish_hat.h");
                    ImGui::EndMenu();
                }
                if (ImGui::MenuItem("Save", "Ctrl+S")) {}
                if (ImGui::MenuItem("Save As..")) {}

                ImGui::Separator();
                if (ImGui::BeginMenu("Options"))
                {
                    static bool enabled = true;
                    ImGui::MenuItem("Enabled", "", &enabled);
                    ImGui::BeginChild("child", ImVec2(0, 60), true);
                    for (int i = 0; i < 10; i++)
                        ImGui::Text("Scrolling Text %d", i);
                    ImGui::EndChild();
                    static float f = 0.5f;
                    static int n = 0;
                    ImGui::SliderFloat("Value", &f, 0.0f, 1.0f);
                    ImGui::InputFloat("Input", &f, 0.1f);
                    ImGui::Combo("Combo", &n, "Yes\0No\0Maybe\0\0");
                    ImGui::EndMenu();
                }

                if (ImGui::BeginMenu("Colors"))
                {
                    float sz = ImGui::GetTextLineHeight();
                    for (int i = 0; i < ImGuiCol_COUNT; i++)
                    {
                        const char* name = ImGui::GetStyleColorName((ImGuiCol)i);
                        ImVec2 p = ImGui::GetCursorScreenPos();
                        ImGui::GetWindowDrawList()->AddRectFilled(p, ImVec2(p.x + sz, p.y + sz), ImGui::GetColorU32((ImGuiCol)i));
                        ImGui::Dummy(ImVec2(sz, sz));
                        ImGui::SameLine();
                        ImGui::MenuItem(name);
                    }
                    ImGui::EndMenu();
                }

                // Here we demonstrate appending again to the "Options" menu (which we already created above)
                // Of course in this demo it is a little bit silly that this function calls BeginMenu("Options") twice.
                // In a real code-base using it would make senses to use this feature from very different code locations.
                if (ImGui::BeginMenu("Options")) // <-- Append!
                {
                    static bool b = true;
                    ImGui::Checkbox("SomeOption", &b);
                    ImGui::EndMenu();
                }

                if (ImGui::BeginMenu("Disabled", false)) // Disabled
                {
                    IM_ASSERT(0);
                }
                if (ImGui::MenuItem("Checked", NULL, true)) {}
                if (ImGui::MenuItem("Quit")) {}
                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }
    }

    void EditorDockableWindowLayer::DrawViewPort()
    {

    }


    EditorViewPortLayer::EditorViewPortLayer(const std::string rName, Oyun::Camera* cam)
        :Oyun::Imgui::ImLayer(rName), mShowStats(false), defaultCamera(cam)
    {
    }

    std::string FpsStr;
    std::string DeltaStr;
    void EditorViewPortLayer::Draw()
    {
        ImGui::Begin(name.c_str());


        int width = ImGui::GetWindowWidth();
        int height = ImGui::GetWindowHeight();

        if (defaultCamera)
        {
            static ImVec4 statsColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
            static ImVec4 backup_color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
           
            defaultCamera->CreateRenderTexture(width, height);
           
            ImGui::Checkbox("Stats", &mShowStats);
            
            ImGui::Image((void*)(intptr_t)(defaultCamera->RenderTexture->id),
                ImVec2(width, height), ImVec2(0, 1), ImVec2(1, 0));
            
            if (mShowStats)
            {
                FpsStr = "Fps: " + std::to_string(Oyun::gInstantFps);
                DeltaStr = "Delta Time: " + std::to_string(Oyun::gDeltaTime);
                
                ImGui::SetCursorPos(ImVec2(10.0f, 60.0f));
                ImGui::TextColored(statsColor, FpsStr.c_str());
                ImGui::SetCursorPos(ImVec2(10.0f, 75.0f));
                ImGui::TextColored(statsColor, DeltaStr.c_str());
            }

                     
        }
        ImGui::End();
    }

    EditorPropertiesLayer::EditorPropertiesLayer(const std::string rName)
        :Oyun::Imgui::ImLayer(rName)
    {
    }


    void EditorPropertiesLayer::Draw()
    {
        ImGui::Begin(name.c_str());
        
        ImGui::End();
    }
}