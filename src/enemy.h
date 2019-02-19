#include "main.h"
#include "ball.h"
#include "figure.h"

#ifndef ENEMY_H
#define ENEMY_H

class Rope {
public:
    Rope() {}
    Rope(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(glm::vec3 v);
    void tick(int type);
    int move(float x , float y,float z);
private:
    VAO *object;
};

class Parachute {
public:
    Parachute() {}
    Parachute(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    Sphere balloon;
    Ball box ;
    Rope rope[4];
    void draw(glm::mat4 VP);
    void set_position(glm::vec3 v);
    void tick();
    int move(float x , float y,float z);
private:
    VAO *object;
};

Parachute create_parachute(glm::vec3 v);

#endif // ENEMY_H
