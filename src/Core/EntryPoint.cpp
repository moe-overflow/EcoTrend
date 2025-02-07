#include <iostream>

#include "App.hpp"

int main(int argc, char** argv) 
{
	auto& app = App::Instance();
	app.Run();
}

