#include "Renderer.h"
#include "../Objects/Scene.h"
#include <iostream>

void Renderer::Render(Canvas& canvas, Scene& scene, Camera& camera, int samples) {
    for (int Y = 0; Y < canvas.m_height; Y++) {
        for (int X = 0; X < canvas.m_width; X++) {
            color3 Color{ 0, 0, 0 };
            for (int S = 0; S < samples; S++) {
                // Get normalized U, V coordinates from screen X and Y
                // Add random value to screen X and Y for anti-aliasing
                glm::vec2 Point = glm::vec2{ Random01() + X, Random01() + Y } / glm::vec2{ canvas.m_width, canvas.m_height };

                // Flip Y
                Point.y = 1.0f - Point.y;

                // Create ray from camera
                Ray ray = camera.PointToRay(Point);

                // Cast ray into scene, get color 
                RaycastHit raycasthit;

                // Add trace color value to color
                Color += scene.Trace(ray, 0.001f, 1000.0f, raycasthit, 5);
            }
            //Color = (color3)((Color.r + Color.g + Color.b) / (float)3);
            Color /= samples;
            //color3 Color = scene.Trace(ray, 0.001f, 1000.0f, raycasthit, 5);
            canvas.DrawPoint({ X, Y }, color4(Color, 1));
        }
    }
}

bool Renderer::Initialize() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

void Renderer::Shutdown() {
    if (m_window) SDL_DestroyWindow(m_window);
    if (m_renderer) SDL_DestroyRenderer(m_renderer);

    SDL_Quit();
}

bool Renderer::CreateWindow(int width, int height) {
    m_window = SDL_CreateWindow("Ray Tracer", 100, 100, width, height, SDL_WINDOW_SHOWN);
    if (m_window == nullptr) {
        std::cout << "SDL Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (m_renderer == nullptr) {
        std::cout << "SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void Renderer::CopyCanvas(const Canvas& canvas) {
    SDL_RenderCopy(m_renderer, canvas.m_texture, nullptr, nullptr);
}

void Renderer::Present() {
    SDL_RenderPresent(m_renderer);
}

color3 Renderer::GetBackgroundFromRay(const Ray& ray) {
    glm::vec3 Direction = glm::normalize(ray.Direction);
    float T = 0.5f * (Direction.y + 1.0f);

    return Lerp(color3{ 1.0f }, color3{ 0.5f, 0.7f, 1.0f }, T);
}