#include "CanvasLayer.hpp"

#include <imgui.h>
#include "CanvasImage.hpp"
#include "Canvas.hpp"

using namespace ImGui;

void CanvasLayer::OnRender()
{
    // Canvas Header
    {
        ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(12, 122, 223, 255));
        Begin("Canvas Header");

        if (Button("Add sample chart"))
            _canvas->InsertImage("./snapshot.png");

        //if (Button("Save as pdf"))
        //    SavePdf();

        _canvas->Render();


        End();

        ImGui::PopStyleColor();
    }

}


