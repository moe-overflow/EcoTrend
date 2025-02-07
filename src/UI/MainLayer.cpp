#include "MainLayer.hpp"

using namespace ImGui;

void MainLayer::OnRender()
{

	Begin("Main");
	// _canvas->Render();
	if (BeginTabBar("Switch"))
	{
		if (BeginTabItem("Plot"))
		{
			_plot_viewer->OnRender();
			EndTabItem();
		}
		if (BeginTabItem("Canvas"))
		{
			_canvas_layer->OnRender(); 
			EndTabItem();
		}

		EndTabBar();
	}

	End();


	
}
