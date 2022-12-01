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
		for (int I = 0; I < 1000; I++) {
			canvas.DrawPoint({ Random(0, 600), Random(0, 400) }, { 1, 1, 1, 1 });
		}
		canvas.Update();

		renderer.CopyCanvas(canvas);
		renderer.Present();
	}

	renderer.Shutdown();

	return 0;
}