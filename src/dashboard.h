#include "main.h"
#include "figure.h"

#ifndef DASHBOARD_H
#define DASHBOARD_H


class Fuel {
public:
    Fuel() {}
    Fuel(int scene);
    glm::vec3 position;
    float rotation;
    float length;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
    int move(float x , float y,float z);
private:
    VAO *object;
};

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

#endif // DASHBOARD_H
