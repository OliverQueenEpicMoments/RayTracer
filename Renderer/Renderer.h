#pragma once
#include "Canvas.h"
#include <SDL.h>
#include "../Math/Ray.h"

class Renderer {
public:
	Renderer() = default;

	void Render(Canvas& canvas);
	
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