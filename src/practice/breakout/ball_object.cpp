#include "ball_object.h"

BallObject::BallObject():Radius(12.5f), Stuck(true){ }

BallObject::BallObject(glm::vec2 pos, float radius, glm::vec2 velocity, Texture2D sprite):
    Radius(radius), Stuck(true) { 
        this->Position = pos;
        this->Velocity = velocity;
        this->Size = glm::vec2(radius*2);
        this->Sprite = sprite;
    }

glm::vec2 BallObject::Move(float dt, unsigned int window_width)
{
    //如果没有触碰到下面的挡板
    if(!this->Stuck)
    {
        this->Position += this->Velocity * dt;
        if(this->Position.x < 0.0f)
        {
            this->Position.x = 0.0f;
            this->Velocity.x = -this->Velocity.x;
        }
        if(this->Position.x + this->Size.x > window_width)
        {
            this->Position.x = window_width - this->Size.x;
            this->Velocity.x = -this->Velocity.x;
        }

        if(this->Position.y < 0.0f)
        {
            this->Position.y = 0.0f;
            this->Velocity.y = -this->Velocity.y;
        }
    }
    return this->Position;
}

void BallObject::Reset(glm::vec2 position, glm::vec2 velocity)
{
    this->Position = position;
    this->Velocity = velocity;
    this->Stuck = true;
}

 void BallObject::Draw(SpriteRenderer& renderer)
 {
    GameObject::Draw(renderer);
 }

