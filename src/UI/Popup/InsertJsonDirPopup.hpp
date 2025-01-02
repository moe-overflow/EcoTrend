#pragma once

#include "../Layer.hpp"
#include "imgui.h"

class InsertJsonDirPopup : public Layer
{
public:
    inline virtual void OnRender() override
    {
        if (ImGui::Button("Insert JSON directory"))
        {
            ImGui::OpenPopup("Select Item Popup");
        }

        if (ImGui::BeginPopup("Select Item Popup"))
        {
            ImGui::Text("ba");
            if(ImGui::InputText("Insert file name", const_cast<char *>(_inserted_file_name.c_str()), 15))
            {

            }
            ImGui::EndPopup();
        }
    }

    [[nodiscard]] LayerType GetType() const override { return LayerType::Popup; }

private:
    std::string _inserted_file_name;

};
