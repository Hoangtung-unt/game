#include "map.h"
#include <fstream>
#include <SDL_image.h>

Map::Map(SDL_Renderer* renderer) : renderer(renderer) {
    LoadTile(0, "assets/3.png");
    LoadTile(1, "assets/2.png");
    // Thêm tile mới nếu có: LoadTile(2, "assets/water.png");

    LoadMap("assets/map.txt");
}

Map::~Map() {
    for (auto& pair : tileTextures) {
        SDL_DestroyTexture(pair.second);
    }
}

void Map::LoadTile(int id, const std::string& path) {
    SDL_Surface* surface = IMG_Load(path.c_str());
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    tileTextures[id] = texture;
}

void Map::LoadMap(const std::string& filename) {
    std::ifstream file(filename);
    for (int i = 0; i < MAP_ROWS; ++i) {
        for (int j = 0; j < MAP_COLS; ++j) {
            file >> tileMap[i][j];
        }
    }
}

void Map::Render(SDL_Rect camera) {
    for (int i = 0; i < MAP_ROWS; ++i) {
        for (int j = 0; j < MAP_COLS; ++j) {
            int tileID = tileMap[i][j];

            // 👇 Bỏ qua nếu là tile trống (-1)
            if (tileID == -1 || tileTextures.count(tileID) == 0)
                continue;

            SDL_Rect dst = {
                j * TILE_SIZE - camera.x,
                i * TILE_SIZE - camera.y,
                TILE_SIZE, TILE_SIZE
            };
            SDL_RenderCopy(renderer, tileTextures[tileID], nullptr, &dst);
        }
    }
}
