#include "main.h"
#include "ball.h"
#include "polygon.h"

#ifndef BACKGROUND_H
#define BACKGROUND_H

struct Island{
    Ball part1,part2,part3;
    glm::vec3 position ;
};

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
    std::vector<Island> islands;
    void create();
private:
    VAO *object;
};

class Volcano {
public:
    Volcano() {}
    Volcano(float x, float y,float z);
    glm::vec3 position;
    float top,bottom, height;
    Polygon part1,part2;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick(int type);
private:
    VAO *object;
};



#endif // BACKGROUND_H