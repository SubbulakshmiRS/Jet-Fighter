#include "main.h"

#ifndef BONUS_H
#define BONUS_H


class Ring {
public:
    Ring() {}
    Ring(float x, float y, float z , glm::vec3 rvec);
    glm::vec3 position,rvec;
    float rotation;
    float size;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
    int move(float x , float y,float z);
    double speed;
private:
    VAO *object;
};

#endif // BONUS_H
