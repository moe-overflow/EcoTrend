#pragma once

#include <vector>
#include <string>
#include <memory>

#include "../Layer.hpp"
#include "Canvas.hpp"

class CanvasLayer : public Layer
{
public:	
	
	virtual void OnRender() override;

	[[nodiscard]] LayerType GetType() const override { return LayerType::Canvas; }



private:

	std::unique_ptr<Canvas> _canvas = std::make_unique<Canvas>();


};