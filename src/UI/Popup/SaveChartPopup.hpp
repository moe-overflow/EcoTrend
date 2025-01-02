#pragma once

#include <iostream>
#include "../Layer.hpp"

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "implot.h"

#include <glad/glad.h>
#include <vector>

#include "../../../vendor/stb/stb_image_write.h"
#include "../Core/App.hpp"

class SaveChartPopup : public Layer
{
public:
    virtual void OnRender() override
    {
        if (ImGui::Button("Save chart..."))
        {
            App::Instance().GetWindow().SaveChart();
        }
    }

    [[nodiscard]] LayerType GetType() const override { return LayerType::Popup; }

};

