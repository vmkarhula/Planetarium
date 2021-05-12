#include <iostream>

#include "PlanetariumApp.h"



int main(int argc, char* argv[]) {

	PlanetariumApp* app = new PlanetariumApp();

	app->Init();
	app->Run();
	
}

