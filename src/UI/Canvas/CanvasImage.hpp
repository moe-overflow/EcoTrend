#pragma once

#include "imgui.h"

struct CanvasImage
{
	ImTextureID texture_id;
	ImVec2 pos;
	ImVec2 size;

	bool x = false;
	ImVec2 offset;
};

