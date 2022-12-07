#include "Renderer.h"
#include "../Objects/Scene.h"
#include <iostream>

void Renderer::Render(Canvas& canvas, Scene& scene) {
    // Camera / Viewport
    glm::vec3 LowerLeft{ -2, -1, -1 };
    glm::vec3 Eye{ 0, 0, 0 };
    glm::vec3 Right{ 4, 0, 0 };
    glm::vec3 Up{ 0, 2, 0 };

    for (int Y = 0; Y < canvas.GetHeight(); Y++) {
        for (int X = 0; X < canvas.GetWidth(); X++) {
            // Get normalized U, V coordinates for X and Y
            float U = X / (float)canvas.GetWidth();
            float V = 1 - (Y / (float)canvas.GetHeight());

            // Create ray
            glm::vec3 Direction = LowerLeft + (U * Right) + (V * Up);
            Ray ray{ Eye, Direction };

            RaycastHit raycasthit;

            color3 Color = scene.Trace(ray, 0.01f, 1000.0f, raycasthit, 5);
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