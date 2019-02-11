#include "background.h"
#include "main.h"


Background ::Background(int scene) {
    //float x = 0,y=0,z=10.0f;
    this->position = glm::vec3(0,-10.0f,0);
    this->rotation = -3;
    GLfloat vertex_buffer_data[2*9] ={
        10000.0f,0,-10000.0f,
        -10000.0f,0,10000.0f,
        -10000.0f,0,-10000.0f,
        10000.0f,0,-10000.0f,
        10000.0f,0,10000.0f,
        -10000.0f,0,10000.0f,

    };

    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data,COLOR_SEA_BLUE, GL_FILL);
    //this->part = Ball(0,0,10,10.0f,COLOR_RED);
}

void Background::draw(glm::mat4 VP) {
    //this->part.draw(VP);
    Matrices.model = glm::mat4(0.5f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Background::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void Background::tick(int type) {
    // type is to differentiate between the different directions of the 2 balls 
     //this->rotation += type;
     //this->position.x -= type*speed;
    //this->position.y -= type*speed;
}

int Background::move(float x , float y,float z){

    this->position.x += x;
    this->position.y += y;
    // check if the item is within the boundaries of the screen ( += 10 all sides)
    return 0;
}
