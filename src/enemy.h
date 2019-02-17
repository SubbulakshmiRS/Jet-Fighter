#include "main.h"
#include "ball.h"
#include "figure.h"

#ifndef ENEMY_H
#define ENEMY_H


class Parachute {
public:
    Parachute() {}
    Parachute(float x, float y, float z,color_t color,float size,int n,float rotation);
    glm::vec3 position,rotate_vec;
    float rotation;
    float size;
    void draw(glm::mat4 VP,glm::vec3 rotate_vec);
    void draw1(glm::mat4 VP,glm::vec3 rotate_vec,glm::mat4 mat);
    void draw2(glm::mat4 VP,glm::mat4 mat);
    void set_position(glm::vec3 v);
    void tick(int type);
    int move(float x , float y,float z);
    double speed;
private:
    VAO *object;
};

#endif // ENEMY_H
