#pragma once

#include <imgui.h>
#include <imgui_internal.h>
#include "../../Core/App.hpp"

struct CanvasImage
{
	ImTextureID texture_id;
	ImVec2 pos; // position of the image, relative to the canvas (not to the main window)
	ImVec2 size;

    void HandleImageDraging()
    {
        using namespace ImGui;

        auto p_min = ImGui::GetWindowPos();
        auto p_max = ImVec2(p_min.x + ImGui::GetWindowWidth(), p_min.y + ImGui::GetWindowHeight());

        if (IsMouseHoveringRect(p_min, p_max) && IsMouseDragging(ImGuiMouseButton_Left))
        {
            pos.x += GetIO().MouseDelta.x;
            pos.y += GetIO().MouseDelta.y;

            ImVec2 screen_size = GetIO().DisplaySize;
            pos.x = ImClamp(pos.x, 0.0f, screen_size.x - size.x);
            pos.y = ImClamp(pos.y, 0.0f, screen_size.y - size.y);
        }


        {
            Text("size");
            Text("Min: %f, %f", p_min.x, p_min.y);
            Text("Max: %f, %f", p_max.x, p_max.y);

            ImVec2 windowPos = ImGui::GetCursorScreenPos();
            const float a4Width = 793.0f;
            const float a4Height = 1122.0f;
            auto window = ImVec2(windowPos.x + a4Width, windowPos.y + a4Height);

            Text("window");
            Text("windowPos Min: %f, %f", windowPos.x, windowPos.y);
            Text("window Max: %f, %f", window.x, window.y);

            // auto mouse_position = App::Instance().GetWindow().GetMousePosition();
            // Text("Mouse position: %f, %f", mouse_position.first, mouse_position.second);
            
            auto mouse_position = App::Instance().GetWindow().GetMousePosition();
            Text("Mouse position: %f, %f", mouse_position.first, mouse_position.second);
        }

    }

    void HandleImageKeys()
    {
        using namespace ImGui;

        if (IsMouseHoveringRect(pos, size) && IsMouseDragging(ImGuiMouseButton_Left))
        {
            pos.x += GetIO().MouseDelta.x;
            pos.y += GetIO().MouseDelta.y;
        }

        ImVec2 move = ImVec2(0.0f, 0.0f);
        const float speed = 10.0f;

        if (IsKeyPressed(ImGuiKey_LeftArrow))   move.x -= speed;
        if (IsKeyPressed(ImGuiKey_RightArrow))  move.x += speed;
        if (IsKeyPressed(ImGuiKey_UpArrow))     move.y -= speed;
        if (IsKeyPressed(ImGuiKey_DownArrow))   move.y += speed;
        
        pos.x += move.x;
        pos.y += move.y;

        // This is necessary for making the image staying inside of layer (boundries)
        ImVec2 screen_size = GetIO().DisplaySize;
        pos.x = ImClamp(pos.x, 0.0f, screen_size.x - size.x);
        pos.y = ImClamp(pos.y, 0.0f, screen_size.y - size.y);
    }


};

