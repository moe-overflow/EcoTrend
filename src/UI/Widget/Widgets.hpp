#pragma once

#include <string>
#include <vector>
#include <array>
#include "../../Template/Template.hpp"

struct SliderData
{
    std::string Label;
    int Index;
    int Min, Max;
};

struct ComboWidget
{
    std::string Label;
    int Index;
    std::vector<std::string> ListContent;
    // size_t ElementCount;
};

struct ColorPickerWidget
{
    std::string Label;
    Color Color;
};

void OnRenderSlider(SliderData& slider_data);

void OnRenderCombo(ComboWidget& combo);

void OnRenderColorPicker(ColorPickerWidget& color_picker_widget);

