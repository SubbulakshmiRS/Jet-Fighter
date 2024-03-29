#include "dashboard.h"
#include "main.h"

Dashboard ::Dashboard(int scene) {
    this->position = glm::vec3(5,-7.5f,0);
    this->rotation = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    
    this->part1 = Semi(this->position.x,this->position.y,0,COLOR_DEAD_BLACK,2.5f,20);
    this->part2 = Semi(this->position.x,this->position.y,0,COLOR_BLACK,2.0f,10);
    GLfloat vertex_buffer_data[3*3] ={
        0,0,0,
        -0.05f,2.0f,0,
        0.05f,2.0f,0,
    };

    this->object = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data, COLOR_BACKGROUND , GL_FILL);
}

void Dashboard::draw(glm::mat4 VP) {
    this->part1.draw(VP);
    this->part2.draw(VP);
    Matrices.model = glm::mat4(0.5f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f),glm::vec3(0,0,1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Dashboard::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void Dashboard::tick(int type) {
    // type is to differentiate between the different directions of the 2 balls 
     //this->rotation += type;
     //this->position.x -= type*speed;
    //this->position.y -= type*speed;
}

int Dashboard::move(float x , float y,float z){

    this->position.x += x;
    this->position.y += y;
    this->position.z += z;
    // check if the item is within the boundaries of the screen ( += 10 all sides)
    return 0;
}

Compass ::Compass(int scene) {
    this->position = glm::vec3(5,-3,0);
    this->rotation = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    
    this->part1 = Polygon(this->position.x,this->position.y,this->position.z,COLOR_GOLD,1.5f,20,0);
    this->part2 = Polygon(this->position.x,this->position.y,this->position.z,COLOR_BACKGROUND,1.0f,20,0);
    GLfloat vertex_buffer_data[3*3] ={
        0,0,0,
        -0.1f,1.5f,0,
        0.1f,1.5f,0,
    };

    this->object = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data, COLOR_DEAD_BLACK , GL_FILL);
}

void Compass::draw(glm::mat4 VP) {
    this->part1.draw(VP,glm::vec3(0,0,1));
    this->part2.draw(VP,glm::vec3(0,0,1));
    Matrices.model = glm::mat4(0.5f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f),glm::vec3(0,0,1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Compass::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void Compass::tick(int type) {
    // type is to differentiate between the different directions of the 2 balls 
     //this->rotation += type;
     //this->position.x -= type*speed;
    //this->position.y -= type*speed;
}

int Compass::move(float x , float y,float z){

    this->position.x += x;
    this->position.y += y;
    this->position.z += z;
    // check if the item is within the boundaries of the screen ( += 10 all sides)
    return 0;
}

Fuel ::Fuel(int scene) {
    this->position = glm::vec3(0,7.0f,0);
    this->rotation = 0;
    this->length =7.75f;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    
    GLfloat vertex_buffer_data[6*3] ={
        (-1)*this->length,0.5f,0,
        (-1)*this->length,-0.5f,0,
        this->length,-0.5f,0,
        (-1)*this->length,0.5f,0,
        this->length,-0.5f,0,
        this->length,0.5f,0,
    };

    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data , COLOR_MAROON , GL_FILL);
}

void Fuel::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.5f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f),glm::vec3(0,0,1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Fuel::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void Fuel::tick() {
    GLfloat vertex_buffer_data[6*3] ={

        (-1)*this->length,0.5f,0,
        (-1)*this->length,-0.5f,0,
        this->length,-0.5f,0,
        (-1)*this->length,0.5f,0,
        this->length,-0.5f,0,
        this->length,0.5f,0,

    };

this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, COLOR_MAROON , GL_FILL);
}

int Fuel::move(float x , float y,float z){

    this->position.x += x;
    this->position.y += y;
    this->position.z += z;
    // check if the item is within the boundaries of the screen ( += 10 all sides)
    return 0;
}



