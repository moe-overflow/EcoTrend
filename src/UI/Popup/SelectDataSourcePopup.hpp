#pragma once

#include "../Layer.hpp"
#include "imgui.h"

class SelectChartTypePopup : public Layer
{
public:
    inline virtual void OnRender() override
    {
        if (ImGui::Button("Choose chart type"))
        {
            ImGui::OpenPopup("Select Item Popup");
        }

        if (ImGui::BeginPopup("Select Item Popup"))
        {

            ImGui::EndPopup();
        }
    }



private:





};
