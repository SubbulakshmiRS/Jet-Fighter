#include "main.h"
#include "polygon.h"
#include "ball.h"

#ifndef PLANE_H
#define PLANE_H

struct Bullet{
    Ball b;
    glm::vec3 velocity;
};

struct Bomb{
    Ball b;
    glm::vec3 velocityh;
    float velocityv;
};

class Plane {
public:
    Plane() {}
    Plane(float x, float y, float z);
    glm::vec3 position,rotate_vec;
    Polygon part1,part2,part3,part4;
    float rotation,speed_x,speed_y,speed_z;
    float fuel,points;
    void draw(glm::mat4 VP);
    void set_position(glm::vec3 v);
    void tick();
    int move(float x , float y,float z);
    void tilt_left();
    void tilt_right();
    void rotate_c();
    void rotate_cc();
    void shoot(int type);
    std::vector <Bullet> bullets;
    std::vector <Bomb> bombs;

private:
    VAO *object;
};

#endif // PLANE_H