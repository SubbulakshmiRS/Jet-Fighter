#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, float z,float size ,color_t color);
    glm::vec3 position;
    float rotation;
    float size;
    void draw(glm::mat4 VP);
    void set_position(glm::vec3 v);
    void tick(int type);
    double speed;
private:
    VAO *object;
};

#endif // BALL_H
