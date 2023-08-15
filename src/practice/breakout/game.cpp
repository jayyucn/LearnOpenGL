#include "game.h"
#include "resource_manager.h"
#include "sprite_renderer.h"


SpriteRenderer  *Renderer;
GameObject      *Player;
BallObject      *Ball;


Game::Game(unsigned int width, unsigned int height):State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{

}

Game::~Game()
{
    delete Renderer;
    delete Player;
    delete Ball;
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
    GameLevel one; one.Load("levels/one.lvl", this->Width, this->Height / 2);
    GameLevel two; two.Load("levels/two.lvl", this->Width, this->Height / 2);
    GameLevel three; three.Load("levels/three.lvl", this->Width, this->Height / 2);
    GameLevel four; four.Load("levels/four.lvl", this->Width, this->Height / 2);
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
    if(this->State != GAME_ACTIVE)
    {
        return;
    }
    Ball->Move(dt, this->Width);
    this->DoCollisions(dt);
    if(Ball->Position.y >= this->Height)
    {
        this->ResetLevel();
        this->ResetPlayer();
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

void Game::ResetLevel()
{
    if (this->Level == 0)
        this->Levels[0].Load("levels/one.lvl", this->Width, this->Height / 2);
    else if (this->Level == 1)
        this->Levels[1].Load("levels/two.lvl", this->Width, this->Height / 2);
    else if (this->Level == 2)
        this->Levels[2].Load("levels/three.lvl", this->Width, this->Height / 2);
    else if (this->Level == 3)
        this->Levels[3].Load("levels/four.lvl", this->Width, this->Height / 2);
}

void Game::ResetPlayer()
{
    // reset player/ball stats
    Player->Size = PLAYER_SIZE;
    Player->Position = glm::vec2(this->Width / 2.0f - PLAYER_SIZE.x / 2.0f, this->Height - PLAYER_SIZE.y);
    Ball->Reset(Player->Position + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS, -(BALL_RADIUS * 2.0f)), INITIAL_BALL_VELOCITY);
}

bool CheckCollision(GameObject &ball, GameObject &go);
Collision CheckCollision(BallObject &ball, GameObject &go);
Direction VectorDirection(glm::vec2 closest);

void Game::DoCollisions(float dt)
{
    for(GameObject &box: this->Levels[this->Level].Bricks)
    {
        if(!box.Destroyed)
        {
            Collision collision = CheckCollision(*Ball, box);
            if(std::get<0>(collision))//collision detected
            {
                if(!box.IsSolid)
                    box.Destroyed = true;
                Direction dir = std::get<1>(collision);
                glm::vec2 diff = std::get<2>(collision);
                if(dir == LEFT || dir == RIGHT)
                {
                    Ball->Velocity.x = -Ball->Velocity.x;
                    float penetration = Ball->Radius - std::abs(diff.x);
                    if(dir == LEFT)
                        Ball->Position.x +=  penetration;
                    else
                        Ball->Position.x -= penetration;
                }
                else
                {
                    Ball->Velocity.y = -Ball->Velocity.y;
                    float penetration = Ball->Radius - std::abs(diff.y);
                    if(dir == UP)
                        Ball->Position.y -= penetration;
                    else
                        Ball->Position.y += penetration;
                }

            }
        }
    }
    Collision result = CheckCollision(*Ball, *Player);
    if(!Ball->Stuck && std::get<0>(result))
    {
        float playerCenterX = Player->Position.x + Player->Size.x / 2.0f;
        float distance = (Ball->Position.x + Ball->Radius) - playerCenterX;
        float percentage = distance / (Player->Size.x / 2.0f);
        float strength = 2.0f;
        glm::vec2 oldVelocity = Ball->Velocity;
        Ball->Velocity.x = INITIAL_BALL_VELOCITY.x * percentage * strength;
        Ball->Velocity = glm::normalize(Ball->Velocity) * glm::length(oldVelocity);
        Ball->Velocity.y = -1.0f * abs(Ball->Velocity.y);
    }
}

bool CheckCollision(GameObject &one, GameObject &go)
{
    bool collisionX = one.Position.x + one.Size.x >= go.Position.x && go.Position.x + go.Size.x >= one.Position.x;
    bool collisionY = one.Position.y + one.Size.y >= go.Position.y && go.Position.y + go.Size.y >= one.Position.y;
    return collisionX && collisionY;
}

Collision CheckCollision(BallObject &ball, GameObject &go)
{
    glm::vec2 ballCenter(ball.Position + ball.Radius);
    glm::vec2 aabbHalf(go.Size.x / 2.0f, go.Size.y / 2.0f);
    glm::vec2 goCenter(go.Position.x + aabbHalf.x, go.Position.y + aabbHalf.y);
    glm::vec2 diff = ballCenter - goCenter;
    glm::vec2 clamped = glm::clamp(diff, -aabbHalf, aabbHalf);
    glm::vec2 closest = goCenter + clamped;
    diff = closest - ballCenter;
    
    if(glm::length(diff) < ball.Radius)
        return std::make_tuple(true, VectorDirection(diff), diff);
    else
        return std::make_tuple(false, UP, glm::vec2(0.0f, 0.0f));
}

Direction VectorDirection(glm::vec2 closest)
{
    //指南针，上下左右四个矢量
    glm::vec2 compass[] = {
        glm::vec2(0.0f, 1.0f),//up
        glm::vec2(1.0f, 0.0f),//right
        glm::vec2(0.0f, -1.0f),//down
        glm::vec2(-1.0f, 0.0f),//left
    };
    float  max = 0.0f;
    unsigned int best_match = -1;
    for (int i = 0; i < 4; i++)
    {
        float dot_product = glm::dot(glm::normalize(closest), compass[i]);
        if(dot_product > max)
        {
            max = dot_product;
            best_match = i;
        }
    }
    return (Direction)best_match;
}

