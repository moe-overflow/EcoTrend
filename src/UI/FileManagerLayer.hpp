#pragma once

#include <string>
#include <vector>

#include "Layer.hpp"

class FileManagerLayer : public Layer
{
public:
	virtual void OnRender() override;


private:
	std::vector<std::string> _recent_files;
};
