#pragma once

#include <memory>
#include <string>
#include <vector>

#include "../../Template/Template.hpp"
#include "../../Utility/JsonHandler.hpp"
#include "../Widget/Widgets.hpp"
#include "Layer.hpp"

enum class TextDesignerType
{
    Title,
    Header,
    MeasurementTitle,
    StatisticsText,
    Footer
};

enum class PlotDesignerType
{
    Trend,
    Statistics
};

struct TextDesigner
{
    SliderData FontSizeDesigner;
    ComboWidget FontFamilyDesigner;
    ColorPickerWidget ColorDesigner;

    TextDesignerType Type;
};

struct PlotDesigner
{
    ColorPickerWidget ColorDesigner;
    SliderData LineWidthSlider;
    // SliderData FontSizeSlider;

    PlotDesignerType Type;
};


class TemplateDesigner : public Layer
{
public:
    TemplateDesigner() = delete;

    TemplateDesigner(std::shared_ptr<TemplateStruct> template_struct) : _customer_template_struct{ template_struct } { }

    virtual void OnRender() override;

    virtual void OnAttach() override;

    [[nodiscard]] LayerType GetType() const override
    {
        return LayerType::TemplateDesigner;
    }

    void OnApplyTemplate();

private:
    // Beinhaltet alle Attribute, die zum Erstellen eines Berichtes erforderlich sind (Font size/family, Plot Colors, etc)
    // Kommt von extern (App.hpp), deshalb shared_ptr
    std::shared_ptr<TemplateStruct> _customer_template_struct;
        
    // Beinhaltet Attribute, die ausschließlich mit der GUI zu tun haben / nicht mit dem Bericht
    std::unique_ptr<nlohmann::json> _widget_attributes;
    
    /**/

    // Logo?

    std::array<std::unique_ptr<TextDesigner>, 5> _text_designers;

    std::array<std::unique_ptr<PlotDesigner>, 2> _plot_designers;


    /**/

    void OnRenderTextDesigner(std::unique_ptr<TextDesigner> const& text_designer);

    void OnRenderPlotDesigner(std::unique_ptr<PlotDesigner> const& plot_designer);

    /**/

    void ReadTextDesignersAttributes() const;
    
    void ReadPlotDesignersAttributes() const;

    /**/

    void AssignTextSettings(size_t index, TextAttributes const& settings) const;

    void AssignPlotSettings(size_t index, PlotAttributes const& settings) const;

    /**/

    void ApplyTextAttributes(size_t index, TextAttributes& settings) const;

    void ApplyPlotAttributes(size_t index, PlotAttributes& settings) const;

};
