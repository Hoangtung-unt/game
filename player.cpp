#include "player.h"
#include "map.h"
Player::Player(SDL_Renderer* renderer) {
    SDL_Surface* surfaceRight = IMG_Load("animation/player_right.png");
    textureRight = SDL_CreateTextureFromSurface(renderer, surfaceRight);
    SDL_FreeSurface(surfaceRight);

    SDL_Surface* surfaceLeft = IMG_Load("animation/player_left.png");
    textureLeft = SDL_CreateTextureFromSurface(renderer, surfaceLeft);
    SDL_FreeSurface(surfaceLeft);

    currentTexture = textureRight;

    x = 100;
    y = 0;  // Nhân vật xuất hiện trên cao
    speed = PLAYER_SPEED;

    frame = 0;
    frameCount = 8;
    frameDelay = 8;
    frameDelayCounter = 0;
    moving = false;
    facingLeft = false;

    velocityY = 0;
    onGround = false;
}

void Player::HandleInput(const Uint8* keyState) {
    moving = false;
    if (keyState[SDL_SCANCODE_RIGHT]) {
        x += speed;
        facingLeft = false;
        moving = true;
    }
    if (keyState[SDL_SCANCODE_LEFT]) {
        x -= speed;
        facingLeft = true;
        moving = true;
    }

    // Cập nhật texture tương ứng
    currentTexture = facingLeft ? textureLeft : textureRight;
}

void Player::Update() {
    const int gravity = 1;
    const int maxFallSpeed = 10;
    const int groundLevel = 96;  // Vị trí mặt đất (hàng thứ 3 của tile map)

    if (!onGround) {
        velocityY += gravity;
        if (velocityY > maxFallSpeed)
            velocityY = maxFallSpeed;

        y += velocityY;
    }

    // Va chạm với mặt đất
    if (y + PLAYER_HEIGHT >= groundLevel) {
        y = groundLevel - PLAYER_HEIGHT;
        velocityY = 0;
        onGround = true;
    } else {
        onGround = false;
    }

    // Giới hạn trong bản đồ
    if (x < 0) x = 0;
    if (x + PLAYER_WIDTH > MAP_COLS * TILE_SIZE)
        x = MAP_COLS * TILE_SIZE - PLAYER_WIDTH;
}

void Player::Render(SDL_Renderer* renderer, SDL_Rect camera) {
    SDL_Rect src = {
        frame * PLAYER_WIDTH,
        0,
        PLAYER_WIDTH,
        PLAYER_HEIGHT
    };

    SDL_Rect dst = {
        x - camera.x,
        y - camera.y,
        PLAYER_WIDTH,
        PLAYER_HEIGHT
    };

    SDL_RenderCopy(renderer, currentTexture, &src, &dst);
}

Player::~Player() {
    SDL_DestroyTexture(textureRight);
    SDL_DestroyTexture(textureLeft);
}
