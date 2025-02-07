#pragma once

#include <vector>
#include <string>

#include "CanvasImage.hpp"

// todo: Canvas shouldn't be dockable
class Canvas
{
public:

	const float A4_WIDTH = 793.0f;
	const float A4_HEIGHT = 1122.0f;


	Canvas() : _x_offset(50), _y_offset(50) {}

	void Render();

	void InsertImage(const std::string& path);

	void SavePdf();

	void UpdatePosition();

private:

	ImTextureID LoadImage(const std::string& path);
	std::vector<CanvasImage> _images;

	void RenderImage(CanvasImage& img);

	int _x_offset;
	int _y_offset;

	ImVec2 _position;

};


