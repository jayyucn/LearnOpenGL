#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "game_level.h"

//当前游戏状态
enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

// Initial size of the player paddle
const glm::vec2 PLAYER_SIZE(100.0f, 20.0f);
// Initial velocity of the player paddle
const float PLAYER_VELOCITY(500.0f);

class Game
{
    public:
        GameState               State;
        bool                    Keys[1024];
        unsigned int            Width, Height;
        std::vector<GameLevel>  Levels;
        unsigned int            Level;
        Game(unsigned int width, unsigned int height);
        ~Game();
        void Init();
        void ProcessInput(float dt);
        void Update(float dt);
        void Render();
};

#endif
