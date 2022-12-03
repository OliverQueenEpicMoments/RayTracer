#include "Renderer/Renderer.h"
#include <iostream>

int main(int, char**) {
	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow(600, 400);

	Canvas canvas(600, 400, renderer);

	bool Quit = false;
	while (!Quit) {
		SDL_Event event;
		SDL_PollEvent(&event);
		switch (event.type) {
		case SDL_QUIT:
			Quit = true;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				Quit = true;
				break;
			}
			break;
		}

		// Render Scene
		canvas.Clear({ 0, 0, 0, 0 });
		renderer.Render(canvas);
		canvas.Update();

		renderer.CopyCanvas(canvas);
		renderer.Present();
	}

	renderer.Shutdown();

	return 0;
}