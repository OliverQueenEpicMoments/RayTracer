#include "Renderer/Renderer.h"
#include <iostream>

int main(int, char**) {
	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow(400, 300);

	bool Quit = false;
	while (!Quit) {
		SDL_Event event;
		SDL_PollEvent(&event);
		switch (event.type) {
		case SDL_QUIT:
			Quit = true;
			break;
		}
	}

	renderer.Shutdown();

	return 0;
}