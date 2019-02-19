#include "main.h"
#include "figure.h"
#include "polygon.h"

#ifndef DASHBOARD_H
#define DASHBOARD_H

class Dashboard :public Semi {
public:
    Dashboard() {}
    Dashboard(int scene);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick(int type);
    int move(float x , float y,float z);
    Semi part1, part2;
private:
    VAO *object;
};

class Compass :public Semi {
public:
    Compass() {}
    Compass(int scene);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick(int type);
    int move(float x , float y,float z);
    Polygon part1, part2;
private:
    VAO *object;
};

class Fuel :public Semi {
public:
    Fuel() {}
    Fuel(int scene);
    glm::vec3 position;
    float length;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
    int move(float x , float y,float z);
    Semi part1, part2;
private:
    VAO *object;
};

#endif // DASHBOARD_H
