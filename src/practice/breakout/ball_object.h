#ifndef BALLOBJECT_H
#define BALLOBJECT_H

#include "texture.h"
#include "game_object.h"

#include <glm/glm.hpp>

class BallObject: public GameObject
{
public:
    float Radius;
    bool Stuck;
    
    BallObject();
    BallObject(glm::vec2 pos, float radius, glm::vec2 velocity, Texture2D sprite);

    glm::vec2 Move(float dt, unsigned int window_width);
    void Reset(glm::vec2 position, glm::vec2 velocity);
    void Draw(SpriteRenderer &renderer) override;
};
#endif  