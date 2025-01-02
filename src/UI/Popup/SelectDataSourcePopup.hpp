#pragma once

#include "../Layer.hpp"
#include "imgui.h"

class SelectDataSourcePopup : public Layer
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


    [[nodiscard]] LayerType GetType() const override { return LayerType::Popup; }

private:





};
