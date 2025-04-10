#include "TemplateDesigner.hpp"

#include <imgui.h>
#include <magic_enum/magic_enum.hpp>

#include "../../Core/App.hpp"
#include "../../Template/Template.hpp"
#include "../Widget/Widgets.hpp"

using namespace ImGui;

void TemplateDesigner::OnAttach()
{
    _widget_attributes = std::make_unique<nlohmann::json>(
            JSON_Handler::ReadJsonFile(std::string(TEMPLATE_PATH) + "/customer_template_widgets.json")
    );

    try
    {
        for (size_t i = 0; i < 5; i++)
            _text_designers[i] = std::make_unique<TextDesigner>();

        for (size_t i = 0; i < 2; i++)
            _plot_designers[i] = std::make_unique<PlotDesigner>();

        ReadTextDesignersAttributes();
        ReadPlotDesignersAttributes();
    }
    catch (std::exception& e)
    {
        std::cerr << "Error while init designers: " << e.what() << std::endl;
    }


    AssignTextSettings(0, _customer_template_struct->TitleTextSettings);
    AssignTextSettings(1, _customer_template_struct->HeaderTextSettings);
    AssignTextSettings(2, _customer_template_struct->MeasurementTitleSettings);
    AssignTextSettings(3, _customer_template_struct->StatisticsValuesSettings);
    AssignTextSettings(4, _customer_template_struct->FooterTextSettings);

    AssignPlotSettings(0, _customer_template_struct->TrendPlotSettings);
    AssignPlotSettings(1, _customer_template_struct->StatisticsPlotSettings);
}

void TemplateDesigner::OnRender()
{
    Begin("Template Designer");

    Text("Designing a custom template");

    {

        if (CollapsingHeader("Title"))
            OnRenderTextDesigner(_text_designers[0]);

        if (CollapsingHeader("Logo"))
        {
            // TODO: Make a list of available logos, similar to file manager
            // Or maybe combo?
        }

        if (CollapsingHeader("Header"))
            OnRenderTextDesigner(_text_designers[1]);

        if (CollapsingHeader("Measurement Title"))
            OnRenderTextDesigner(_text_designers[2]);

        if (CollapsingHeader("Statistics Values"))
            OnRenderTextDesigner(_text_designers[3]);

        if (CollapsingHeader("Footer"))
            OnRenderTextDesigner(_text_designers[4]);

        Separator();

        if (CollapsingHeader("Trend Plot"))
            OnRenderPlotDesigner(_plot_designers[0]);

        if (CollapsingHeader("Statistics Plot"))
            OnRenderPlotDesigner(_plot_designers[1]);
    }

    if (Button("Apply"))
        OnApplyTemplate();

    End();
}

void TemplateDesigner::OnApplyTemplate()
{
    // Write members of this class to json (customer_template) ?
    try
    {
        ApplyTextAttributes(0, _customer_template_struct->TitleTextSettings);
        ApplyTextAttributes(1, _customer_template_struct->HeaderTextSettings);
        ApplyTextAttributes(2, _customer_template_struct->MeasurementTitleSettings);
        ApplyTextAttributes(3, _customer_template_struct->StatisticsValuesSettings);
        ApplyTextAttributes(4, _customer_template_struct->FooterTextSettings);

        ApplyPlotAttributes(0, _customer_template_struct->TrendPlotSettings);
        ApplyPlotAttributes(1, _customer_template_struct->StatisticsPlotSettings);

        App::Instance().GetCustomerTemplate()->ApplyToJson(_customer_template_struct);
    }
    catch (std::exception& e)
    {
        std::cerr << "OnApplyTemplate(): " << e.what() << std::endl;
    }
}

void TemplateDesigner::OnRenderTextDesigner(std::unique_ptr<TextDesigner> const& text_designer)
{
    OnRenderSlider(text_designer->FontSizeDesigner);
    OnRenderCombo(text_designer->FontFamilyDesigner);
    OnRenderColorPicker(text_designer->ColorDesigner);
}

void TemplateDesigner::OnRenderPlotDesigner(std::unique_ptr<PlotDesigner> const& plot_designer)
{
    OnRenderSlider(plot_designer->LineWidthSlider);
    OnRenderColorPicker(plot_designer->ColorDesigner);

    Text("Index %d", plot_designer->LineWidthSlider.Index);
    Text("Color (%f, %f, %f)",
         plot_designer->ColorDesigner.Color.R,
         plot_designer->ColorDesigner.Color.G,
         plot_designer->ColorDesigner.Color.B);
}


void TemplateDesigner::ReadTextDesignersAttributes() const
{
    // TODO: replace 3 with enum size or better: read values directly from enum instead of declaring strings
    std::array<std::string, 3> const widget_types = { "Slider", "ComboWidget", "ColorPickerWidget" };

    for (auto& w_type : widget_types)
    {
        for (auto& d_type : magic_enum::enum_values<TextDesignerType>())
        {
            auto const index = magic_enum::enum_integer(d_type);

            if (w_type == widget_types[0])
            {
                _text_designers[index]->FontSizeDesigner.Label =
                        _widget_attributes->at("Text").at(w_type).at(magic_enum::enum_name(d_type)).at("Label");

                _text_designers[index]->FontSizeDesigner.Min =
                        _widget_attributes->at("Text").at(w_type).at(magic_enum::enum_name(d_type)).at("Min");

                _text_designers[index]->FontSizeDesigner.Max =
                        _widget_attributes->at("Text").at(w_type).at(magic_enum::enum_name(d_type)).at("Max");
            }
            else if (w_type == widget_types[1])
            {
                _text_designers[index]->FontFamilyDesigner.Label =
                        _widget_attributes->at("Text").at(w_type).at(magic_enum::enum_name(d_type)).at("Label");

                _text_designers[index]->FontFamilyDesigner.ListContent = _widget_attributes->at("Text")
                                                                                 .at(w_type)
                                                                                 .at(magic_enum::enum_name(d_type))
                                                                                 .at("ListContent")
                                                                                 .get<std::vector<std::string>>();
            }
            else if (w_type == widget_types[2])
            {
                _text_designers[index]->ColorDesigner.Label =
                        _widget_attributes->at("Text").at(w_type).at(magic_enum::enum_name(d_type)).at("Label");
            }
        }
    }
}

void TemplateDesigner::ReadPlotDesignersAttributes() const
{
    std::array<std::string, 2> const widget_types = { "Slider", "ColorPickerWidget" };

    for (auto& w_type : widget_types)
    {
        for (auto& d_type : magic_enum::enum_values<PlotDesignerType>())
        {
            auto const index = magic_enum::enum_integer(d_type);

            if (w_type == widget_types[0])
            {
                _plot_designers[index]->LineWidthSlider.Label =
                        _widget_attributes->at("Plot").at(w_type).at(magic_enum::enum_name(d_type)).at("Label");

                _plot_designers[index]->LineWidthSlider.Min =
                        _widget_attributes->at("Plot").at(w_type).at(magic_enum::enum_name(d_type)).at("Min");

                _plot_designers[index]->LineWidthSlider.Max =
                        _widget_attributes->at("Plot").at(w_type).at(magic_enum::enum_name(d_type)).at("Max");
            }
            else if (w_type == widget_types[1])
            {
                _plot_designers[index]->ColorDesigner.Label =
                        _widget_attributes->at("Plot").at(w_type).at(magic_enum::enum_name(d_type)).at("Label");
            }
        }
    }
}

void TemplateDesigner::AssignTextSettings(size_t index, TextAttributes const& settings) const
{
    _text_designers[index]->FontSizeDesigner.Index = settings.FontSize;
    _text_designers[index]->FontFamilyDesigner.Index = magic_enum::enum_index(settings.FontFamily).value();
    _text_designers[index]->ColorDesigner.Color = { settings.FontColor.R, settings.FontColor.G, settings.FontColor.B };
}

void TemplateDesigner::AssignPlotSettings(size_t index, PlotAttributes const& settings) const
{
    _plot_designers[index]->LineWidthSlider.Index = settings.LineWidth;
    _plot_designers[index]->ColorDesigner.Color = { settings.CurveColor.R,
                                                    settings.CurveColor.G,
                                                    settings.CurveColor.B };
}

void TemplateDesigner::ApplyTextAttributes(size_t index, TextAttributes& settings) const
{
    // clang-format off
    settings = {
        magic_enum::enum_value<FontFamilyOption>(_text_designers[index]->FontFamilyDesigner.Index),
        _text_designers[index]->FontSizeDesigner.Index,
        { 
            _text_designers[index]->ColorDesigner.Color.R, _text_designers[index]->ColorDesigner.Color.G, _text_designers[index]->ColorDesigner.Color.B  
        }
    };
    // clang-format on
}

void TemplateDesigner::ApplyPlotAttributes(size_t const index, PlotAttributes& settings) const
{
    // clang-format off
    settings = {
        { 
            _plot_designers[index]->ColorDesigner.Color.R, _plot_designers[index]->ColorDesigner.Color.G, _plot_designers[index]->ColorDesigner.Color.B
        },
        static_cast<size_t>(_plot_designers[index]->LineWidthSlider.Index)
    };
    // clang-format on
}

