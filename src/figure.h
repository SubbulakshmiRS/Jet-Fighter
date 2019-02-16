#include "main.h"
#include "polygon.h"

#ifndef FIGURE_H
#define FIGURE_H

class Sphere {
public:
    Sphere() {}
    Sphere(float x, float y, float z,color_t color,float size);
    glm::vec3 position;
    float rotation;
    float size;
    float n,m;
    Polygon part[50];
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick(int type);
    int move(float x , float y,float z);
    double speed;
private:
    VAO *object;
};

class Semi {
public:
    Semi() {}
    Semi(float x, float y, float z,color_t color,float size,int n);
    glm::vec3 position;
    float rotation;
    float size;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick(int type);
    int move(float x , float y,float z);
    double speed;
private:
    VAO *object;
};

#endif // FIGURE_H
