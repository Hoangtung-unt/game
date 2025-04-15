#include <SDL.h>
#include <SDL_image.h>
#include "map.h"
#include "camera.h"
#include "player.h"
#include "constants.h"

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    SDL_Window* window = SDL_CreateWindow("Scrolling Map + Camera",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Load map
    Map map(renderer);

    // Tạo player và camera
    Player player(renderer);  // Nhân vật được load từ assets/player.png
    camera camera(SCREEN_WIDTH, SCREEN_HEIGHT, MAP_COLS * TILE_SIZE, MAP_ROWS * TILE_SIZE);

    bool running = true;
    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                running = false;
        }

        // Xử lý phím nhấn
        const Uint8* keyState = SDL_GetKeyboardState(NULL);
        player.HandleInput(keyState);
        player.Update();

        // Camera theo dõi người chơi
        camera.Follow(player.GetX(), player.GetY());

        // Vẽ màn hình
        SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255); // màu nền
        SDL_RenderClear(renderer);
        map.Render(camera.GetView());
        player.Render(renderer, camera.GetView());
        SDL_RenderPresent(renderer);

        SDL_Delay(16); // ~60fps
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
