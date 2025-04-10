#include "Widgets.hpp"

#include <imgui.h>
#include <imgui_stdlib.h>
#include <iostream>

using namespace ImGui;

void OnRenderSlider(SliderData& slider_data)
{
    Text(slider_data.Label.c_str());
    SameLine();
    SliderInt(
            std::string("##Slider: " + slider_data.Label).c_str(),
            &slider_data.Index,
            slider_data.Min,
            slider_data.Max
    );
}

void OnRenderCombo(ComboWidget& combo_widget)
{
    Text(combo_widget.Label.c_str());
    SameLine();
    if (BeginCombo(
                std::string("##ComboWidget: " + combo_widget.Label).c_str(),
                combo_widget.ListContent[combo_widget.Index].c_str()
        ))
    {
        for (int i = 0; i < combo_widget.ListContent.size(); i++)
        {
            bool is_selected = (combo_widget.Index == i);
            if (Selectable(combo_widget.ListContent[i].c_str(), is_selected))
            {
                combo_widget.Index = i;
            }
            if (is_selected)
            {
                SetItemDefaultFocus();
            }
        }
        EndCombo();
    }
}

void OnRenderColorPicker(ColorPickerWidget& color_picker_widget)
{
    Text(color_picker_widget.Label.c_str());
    SameLine();
    SetNextItemWidth(GetWindowSize().x * 0.3);

    float normalizedColor[3] = {
        color_picker_widget.Color.R / 255.0f,
        color_picker_widget.Color.G / 255.0f,
        color_picker_widget.Color.B / 255.0f
    };

    if (ColorPicker3(std::string("##ColorPicker: " + color_picker_widget.Label).c_str(), normalizedColor))
    {
        color_picker_widget.Color.R = normalizedColor[0] * 255.0f;
        color_picker_widget.Color.G = normalizedColor[1] * 255.0f;
        color_picker_widget.Color.B = normalizedColor[2] * 255.0f;
  
    }
}
