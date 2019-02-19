#include "main.h"
#include "ball.h"
#include "polygon.h"
#include "figure.h"

#ifndef BACKGROUND_H
#define BACKGROUND_H

glm::vec3 cross_product(glm::vec3 a,glm::vec3 b);
float dot_product(glm::vec3 a,glm::vec3 b);
float magnitude(glm::vec3 a);

class Volcano {
public:
    Volcano() {}
    Volcano(float x, float y,float z);
    glm::vec3 position;
    float top,bottom, height;
    Polygon part1,part2;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(glm::vec3 v);
    void tick(int type);
private:
    VAO *object;
};

struct Island{
    Ball part1,part2,part3;
    glm::vec3 position ;
    Volcano volcano;
    int present ;
};

class Background {
public:
    Background() {}
    Background(int scene);
    glm::vec3 position;
    int stat;
    Ball part;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(glm::vec3 v);
    void tick(int type);
    int move(float x , float y,float z);
    std::vector<Island> islands;
    void create(glm::vec3 v);
    void delete_element(glm::vec3 p);
private:
    VAO *object;
};

class Arrow {
public:
    Arrow() {}
    Arrow(int scene);
    glm::vec3 position,current_align;
    glm::vec3 align ;
    float rotation;
    void draw(glm::mat4 VP,glm::vec3 p);
    void set_position(glm::vec3 v);
    void tick(int type);
    double speed;
private:
    VAO *object;
};

class Checkpoint {
public:
    Checkpoint() {}
    Checkpoint(float x,float z);
    glm::vec3 position;
    glm::vec3 align ;
    Ball platform ;
    Sphere part1;
    float top , bottom , height ;
    float rotation;
    void draw(glm::mat4 VP,glm::vec3 p);
    void set_position(glm::vec3 v);
    void tick(int type);
    int move(float x , float y,float z);
    double speed;
private:
    VAO *object;
};


#endif // BACKGROUND_H