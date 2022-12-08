#include "Renderer/Renderer.h"
#include "Objects/Sphere.h"
#include "Objects/Scene.h"
#include <iostream>

int main(int, char**) {
	const int Width = 800;
	const int Height = 600;
	const int Samples = 5;

	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow(Width, Height);

	Canvas canvas(Width, Height, renderer);
	Camera camera({ 0, 1, 1 }, { 0, 0, 0 }, { 0, 1, 0 }, 90.0f, Width / (float)Height);
	Scene scene;

	scene.AddObject(std::make_unique<Sphere>(glm::vec3{ 0, 0, -1 }, 0.5f, std::make_unique<Lambertian>(color3{ 1, 0, 0 })));
	scene.AddObject(std::make_unique<Sphere>(glm::vec3{ 1.25f, 0, -1 }, 0.5f, std::make_unique<Metal>(color3{ 1, 1, 1 }, 0.3f)));
	scene.AddObject(std::make_unique<Sphere>(glm::vec3{ 0, -100.5f, -1 }, 100.0f, std::make_unique<Lambertian>(color3{ 0.2f })));

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
		renderer.Render(canvas, scene, camera, Samples);
		canvas.Update();

		renderer.CopyCanvas(canvas);
		renderer.Present();
	}

	renderer.Shutdown();

	return 0;
}