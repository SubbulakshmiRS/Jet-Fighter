#include "main.h"

#ifndef POLYGON_H
#define POLYGON_H


class Polygon {
public:
    Polygon() {}
    Polygon(float x, float y, color_t color,float size,int n,float rotation);
    glm::vec3 position;
    float rotation;
    float size;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(int type);
    int move(float x , float y);
    double speed;
private:
    VAO *object;
};

#endif // POLYGON_H
