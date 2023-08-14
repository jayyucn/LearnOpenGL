#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "game_level.h"
#include "game_object.h"
#include "ball_object.h"

//当前游戏状态
enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

enum Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT
};

typedef std::tuple<bool, Direction, glm::vec2> Collision;

// Initial size of the player paddle
const glm::vec2 PLAYER_SIZE(100.0f, 20.0f);
// Initial velocity of the player paddle
const float PLAYER_VELOCITY(500.0f);
// 球的初始速度
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
// 球半径
const float BALL_RADIUS = 12.5f;

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
    void DoCollisions(float dt);
    // reset
    void ResetLevel();
    void ResetPlayer();
};

#endif
