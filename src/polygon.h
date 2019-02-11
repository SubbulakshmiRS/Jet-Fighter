#include "main.h"

#ifndef POLYGON_H
#define POLYGON_H


class Polygon {
public:
    Polygon() {}
    Polygon(float x, float y, float z,color_t color,float size,int n,float rotation);
    glm::vec3 position,rotate_vec;
    float rotation;
    float size;
    void draw(glm::mat4 VP,glm::vec3 rotate_vec);
    void draw1(glm::mat4 VP,glm::vec3 rotate_vec,glm::mat4 mat);
    void set_position(float x, float y,float z);
    void tick(int type);
    int move(float x , float y,float z);
    double speed;
private:
    VAO *object;
};

#endif // POLYGON_H
