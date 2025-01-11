#pragma once

#include <vector>
#include <string>

#include "CanvasImage.hpp"
#include "../../../vendor/stb/stb_image.h"

class Canvas
{
public:

	Canvas() = default;

	void Render();

	void AddImage(const std::string& path);

private:
	std::vector<CanvasImage> _canvas_images;

	void RenderImage(CanvasImage& img);

	ImTextureID LoadImage(const std::string& path);


};


