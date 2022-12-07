#pragma once
#include "Canvas.h"
#include "Camera.h"
#include "../Math/Ray.h"
#include "../Objects/Object.h"
#include <SDL.h>

class Object;
class Scene;

class Renderer {
public:
	Renderer() = default;

	void Render(Canvas& canvas, Scene& scene, Camera& camera, int samples = 5);
	
	bool Initialize();
	void Shutdown();

	bool CreateWindow(int width, int height);

	void CopyCanvas(const Canvas& canvas);
	void Present();

	friend class Canvas;

private:
	color3 GetBackgroundFromRay(const Ray& ray);

	SDL_Window* m_window{ nullptr };
	SDL_Renderer* m_renderer{ nullptr };
};