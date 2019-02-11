#include "main.h"
#include "ball.h"

#ifndef BACKGROUND_H
#define BACKGROUND_H


class Background {
public:
    Background() {}
    Background(int scene);
    glm::vec3 position;
    Ball part;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick(int type);
    int move(float x , float y,float z);
private:
    VAO *object;
};

#endif // BACKGROUND_H