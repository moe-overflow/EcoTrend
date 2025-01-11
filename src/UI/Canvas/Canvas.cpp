#include "Canvas.hpp"

#include <iostream>

#include "glad/glad.h"
#include <imgui.h>

#include <imgui_internal.h>

using namespace ImGui;

void Canvas::Render()
{
	auto canvas_size = ImVec2(1200, 800);
	auto canvas_pos = ImVec2(1, 1);

	SetCursorPos(canvas_pos);
	InvisibleButton("canvas", canvas_size);
    
    ImVec2 canvas_origin = ImGui::GetCursorScreenPos();
    ImVec2 canvas_end = ImVec2(canvas_origin.x + canvas_size.x, canvas_origin.y + canvas_size.y);
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    for (auto& img : _canvas_images)
        RenderImage(img);

    /**/


    ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 255, 0, 255));
    Text("Alpha Beta Gamma");
    ImGui::PopStyleColor();
    
}

void Canvas::AddImage(const std::string& path)
{
    auto image = LoadImage(path);
    _canvas_images.push_back({
        image,
        ImVec2(100, 100),
        ImVec2(500, 500)
    });

}

void Canvas::RenderImage(CanvasImage& img)
{
#if 0
    // Calculate the image's bounding box
    ImVec2 image_min = img.pos;
    ImVec2 image_max = ImVec2(img.pos.x + img.size.x, img.pos.y + img.size.y);

    // Draw the image
    ImGui::SetCursorScreenPos(img.pos);
    ImGui::Image(img.texture_id, img.size);

    // Check if the mouse is inside the image's bounding box
    bool isHovered = ImGui::IsItemHovered();  // Checks if the mouse is over the image
    bool isClicked = ImGui::IsMouseClicked(0);  // Checks if the left mouse button was clicked

    if (isHovered && isClicked) {
        // Start dragging the image if the mouse is clicked within the bounds
        img.x = true;
        // Store the offset from the mouse position to the image's top-left corner
        img.offset = ImVec2(ImGui::GetMousePos().x - img.pos.x, ImGui::GetMousePos().y - img.pos.y);
    }

    if (img.x) {
        // Update the image's position based on mouse movement
        img.pos = ImVec2(ImGui::GetMousePos().x - img.offset.x, ImGui::GetMousePos().y - img.offset.y);

        // If the mouse button is released, stop dragging
        if (!ImGui::IsMouseDown(0)) {
            img.x = false;
        }
    }

#else

    auto min = img.pos;
    auto max = ImVec2(img.pos.x + img.size.x, img.pos.y + img.size.y);

    if (IsMouseHoveringRect(img.pos, img.size) && IsMouseDragging(ImGuiMouseButton_Left))
    {
        img.pos.x += GetIO().MouseDelta.x;
        img.pos.y += GetIO().MouseDelta.y;

        ImVec2 screen_size = GetIO().DisplaySize;
        img.pos.x = ImClamp(img.pos.x, 0.0f, screen_size.x - img.size.x);
        img.pos.y = ImClamp(img.pos.y, 0.0f, screen_size.y - img.size.y);
    }

    //SetCursorScreenPos(img.pos);
    //Image(img.texture_id, img.size);

    ImDrawList* draw_list = ImGui::GetWindowDrawList();  // Get the current window's draw list
    draw_list->AddImage(img.texture_id, img.pos, max);
    /*if (IsItemHovered && IsItemClicked)
    {
        img.x = true;
        img.offset = ImVec2(GetMousePos().x - img.pos.x, GetMousePos().y - img.pos.y);
        
    }

    if (img.x)
    {
        img.pos = ImVec2(GetMousePos().x - img.pos.x, GetMousePos().y - img.pos.y);
        if (!IsMouseDown(0))
            img.x = false;
    }*/
#endif

}

ImTextureID Canvas::LoadImage(const std::string& path)
{
    int width, height, channels;
    auto image = stbi_load(path.c_str(), &width, &height, &channels, STBI_rgb);

    if (image == nullptr)
        throw(std::string("Failed to load texture"));

    std::cout << "Loaded texture: (" << width << ", " << height << ", " << channels << ")\n";

    GLuint m_texture;
    glGenTextures(1, &m_texture);

    glBindTexture(GL_TEXTURE_2D, m_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    auto image_format = channels == 3 ? GL_RGB : GL_RGBA;

    glTexImage2D(GL_TEXTURE_2D, 0, image_format, width, height, 0, image_format, GL_UNSIGNED_BYTE, image);
    
    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(image);

    return m_texture;
     

}
