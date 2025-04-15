#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "constants.h"

class Player {
public:
    Player(SDL_Renderer* renderer);
    ~Player();

    void HandleInput(const Uint8* keyState);
    void Update();
    void Render(SDL_Renderer* renderer, SDL_Rect camera);

    int GetX() const { return x; }
    int GetY() const { return y; }

private:
    SDL_Texture* textureRight;
    SDL_Texture* textureLeft;
    SDL_Texture* currentTexture;

    int x, y;
    int speed;

    // Animation
    int frame;
    int frameCount;
    int frameDelay;
    int frameDelayCounter;
    bool moving;
    bool facingLeft;

    // Thêm biến cho trọng lực và vận tốc Y
    int velocityY;
    bool onGround;
};

#endif
