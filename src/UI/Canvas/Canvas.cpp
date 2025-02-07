#include "Canvas.hpp"

#include "../../Core/App.hpp"

#include <iostream>
#include "glad/glad.h"
#include <imgui.h>
#include <imgui_internal.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <hpdf.h>

using namespace ImGui;

namespace
{
    void PdfErrorHandler(
        HPDF_STATUS error_no,
        HPDF_STATUS detail_no,
        void* user_data)
    {
        std::cerr << "ERROR: " << 
            "error_no = " << std::hex << error_no << "," <<
            "detail_no = " << std::dec << detail_no << std::endl;
    }
}

void Canvas::Render()
{
    // Canvas
    {
        {
            UpdatePosition();

            // Draw a white rectangle with the A4 dimensions
            GetWindowDrawList()->AddRectFilled(
                _position,
                ImVec2(_position.x + A4_WIDTH, _position.y + A4_HEIGHT),
                IM_COL32(255, 255, 255, 255) // White color
            );

            // For debugging purposes
            {
                Text("Canvas size (relativ to GLFW window): (%f, %f), (%f, %f)", 
                    _position.x, _position.y,
                    _position.x + A4_WIDTH, _position.y + A4_HEIGHT
                );

                auto window_pos = App::Instance().GetWindow().GetWindowPosition();
                Text("Canvas size: canvas upper left(%f, %f), bottom right(%f, %f)",
                    _position.x - window_pos.first,
                    _position.y - window_pos.second,
                    _position.x - window_pos.first + A4_WIDTH,
                    _position.y - window_pos.second + A4_HEIGHT
                );
            }

        }

        for (auto& img : _images)
        {
            RenderImage(img);
            img.HandleImageDraging();

            // todo: This causes somehow an issue when dragging an image with the mouse
            // img.HandleImageKeys(); 
        }
    }

}

void Canvas::RenderImage(CanvasImage& img)
{
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    
    auto image_offset_position = ImVec2(img.pos.x + _position.x, img.pos.y + _position.y);
    draw_list->AddImage(
        img.texture_id,
        image_offset_position,
        ImVec2(image_offset_position.x + img.size.x, image_offset_position.y + img.size.y)
    );

}

void Canvas::SavePdf()
{

    auto pdf = HPDF_New(PdfErrorHandler, nullptr);
    
    if (!pdf)
    {
        std::cerr << "Error: Couldn't create pdf" << std::endl;
        return;
    }

    auto page = HPDF_AddPage(pdf);

    auto height = HPDF_Page_GetHeight(page);
    auto width = HPDF_Page_GetWidth(page);

    auto font = HPDF_GetFont(pdf, "Helvetica", nullptr);
    
    HPDF_Page_SetFontAndSize(page, font, 24);

    /**/

    // Text
    {

        HPDF_Page_BeginText(page);
        HPDF_Page_MoveTextPos(page, 60, height - 105);

        HPDF_Page_SetFontAndSize(page, font, 20);
        HPDF_Page_ShowText(page, "Alpha Beta Gamma");
        HPDF_Page_MoveTextPos(page, 0, -20);
        HPDF_Page_EndText(page);
    }

    // Image
    {
        HPDF_Image image = HPDF_LoadPngImageFromFile(pdf, "snapshot.png");

        auto iw = HPDF_Image_GetWidth(image) * 0.5;
        auto ih = HPDF_Image_GetHeight(image) * 0.5;

        HPDF_Page_SetLineWidth(page, 0.5);

        auto x = 50;
        auto y = HPDF_Page_GetHeight(page) - 850;

        /* Draw image to the canvas. (normal-mode with actual size.)*/
        HPDF_Page_DrawImage(page, image, x, y, iw, ih);

        std::cout << "Loaded image to pdf (iw: " << iw << ", ih: " << ih << ", x: " << x << ", y: " << y << ")" << std::endl;
    }

    HPDF_SaveToFile(pdf, "TrendReport.pdf");

    HPDF_Free(pdf);
}

void Canvas::UpdatePosition()
{
    // Get the current window's position and size

    _position = ImGui::GetCursorScreenPos(); // This gets the position of the current window's cursor
    _position.x += _x_offset;
    _position.y += _y_offset; // todo: Darüber kann das Rechteck in die Mitte zentriert werden
}

void Canvas::InsertImage(const std::string& path)
{
    auto image = LoadImage(path);
    _images.push_back({
        image,
        ImVec2(0, 0), // todo: pos should be determined depending on the canvas position
        ImVec2(300, 300)
    });
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

    // return reinterpret_cast<ImTextureID>(static_cast<uintptr_t>(m_texture));
    return m_texture;
}
