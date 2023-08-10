#include "game.h"
#include "resource_manager.h"
#include "sprite_renderer.h"
#include "game_object.h"
#include "ball_object.h"

SpriteRenderer  *Renderer;
GameObject      *Player;
BallObject      *Ball;

// 球的初始速度
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
// 球半径
const float BALL_RADIUS = 12.5f;


Game::Game(unsigned int width, unsigned int height):State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{

}

Game::~Game()
{
    delete Renderer;
    delete Player;
}

void Game::Init()
{
    //加载shaders
    ResourceManager::LoadShader("breakout/sprite.vs", "breakout/sprite.fs", nullptr, "sprite");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width), static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
    Shader shader = ResourceManager::GetShader("sprite");
    shader.Use().SetInteger("image", 0);
    shader.SetMatrix4("projection", projection);
    Renderer = new SpriteRenderer(shader);
    ResourceManager::LoadTexture("background.jpg", false, "background");
    ResourceManager::LoadTexture("awesomeface.png", true, "face");
    ResourceManager::LoadTexture("block.png", false, "block");
    ResourceManager::LoadTexture("block_solid.png", false, "block_solid");
    ResourceManager::LoadTexture("paddle.png", true, "paddle");
    GameLevel one; one.Load("resources/levels/one.lvl", this->Width, this->Height / 2);
    GameLevel two; two.Load("resources/levels/two.lvl", this->Width, this->Height / 2);
    GameLevel three; three.Load("resources/levels/three.lvl", this->Width, this->Height / 2);
    GameLevel four; four.Load("resources/levels/four.lvl", this->Width, this->Height / 2);
    this->Levels.push_back(one);
    this->Levels.push_back(two);
    this->Levels.push_back(three);
    this->Levels.push_back(four);
    this->Level = 0;
    // configure game objects
    glm::vec2 playerPos = glm::vec2(this->Width / 2.0f - PLAYER_SIZE.x / 2.0f, this->Height - PLAYER_SIZE.y);
    Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));
    //ball
    glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2 - BALL_RADIUS, -BALL_RADIUS * 2);
    Ball = new BallObject(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY, ResourceManager::GetTexture("face"));
}

void Game::Update(float dt)
{
    if(this->State == GAME_ACTIVE)
    {
        float maxY = Player->Position.y;
        glm::vec2 range = glm::vec2(Player->Position.x, Player->Position.x + Player->Size.x);
        Ball->Move(dt, this->Width);
    }
}

void Game::ProcessInput(float dt)
{
    if (this->State == GAME_ACTIVE)
        {
            float velocity = PLAYER_VELOCITY * dt;
            // move playerboard
            if (this->Keys[GLFW_KEY_A])
            {
                if (Player->Position.x >= 0.0f)
                    Player->Position.x -= velocity;
                    if(Ball->Stuck)
                        Ball->Position.x -= velocity;
            }
            if (this->Keys[GLFW_KEY_D])
            {
                if (Player->Position.x <= this->Width - Player->Size.x)
                    Player->Position.x += velocity;
                    if(Ball->Stuck)
                        Ball->Position.x += velocity;
            }
            if(this->Keys[GLFW_KEY_SPACE])
            {
                Ball->Stuck = false;
            }
        }
}

void Game::Render()
{
     if(this->State == GAME_ACTIVE)
    {
        Texture2D texture = ResourceManager::GetTexture("background");
        // draw background
        Renderer->DrawSprite(texture, glm::vec2(0.0f, 0.0f), glm::vec2(this->Width, this->Height), 0.0f);
        // draw level
        this->Levels[this->Level].Draw(*Renderer);
        // draw player
        Player->Draw(*Renderer);
        //draw ball
        Ball->Draw(*Renderer);
    }
}

bool Game::CheckCollision(BallObject &one, GameObject &two)
{
    glm::vec2 ballCenter(one.Position + one.Radius);
    glm::vec2 aabbHalf(two.Size / 2);
    glm::vec2 goCenter(two.Position + aabbHalf);
    glm::vec2 diff = ballCenter - goCenter;
    glm::vec2 clamped = glm::clamp(diff, -aabbHalf, aabbHalf);
    glm::vec2 closest = aabbHalf + clamped;
    diff = closest - ballCenter;
    return glm::length(diff) < one.Radius;
}

