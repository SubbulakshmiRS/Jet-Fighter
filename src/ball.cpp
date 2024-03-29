#include "ball.h"
#include "main.h"

Ball::Ball(float x, float y, float z ,float size ,color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->size = size;
    speed = 0.05;
    //std::cout<<"size of ball "<<this->size<<"\n";
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    const GLfloat vertex_buffer_data[] = {
        (-1)*(this->size),(-1)*(this->size),(-1)*(this->size), // triangle 1 : begin
        (-1)*(this->size),(-1)*(this->size), this->size,
        (-1)*(this->size), this->size, this->size, // triangle 1 : end
        this->size, this->size,(-1)*(this->size), // triangle 2 : begin
        (-1)*(this->size),(-1)*(this->size),(-1)*(this->size),
        (-1)*(this->size), this->size,(-1)*(this->size), // triangle 2 : end
        this->size,(-1)*(this->size), this->size,
        (-1)*(this->size),(-1)*(this->size),(-1)*(this->size),
        this->size,(-1)*(this->size),(-1)*(this->size),
        this->size, this->size,(-1)*(this->size),
        this->size,(-1)*(this->size),(-1)*(this->size),
        (-1)*(this->size),(-1)*(this->size),(-1)*(this->size),
        (-1)*(this->size),(-1)*(this->size),(-1)*(this->size),
        (-1)*(this->size), this->size, this->size,
        (-1)*(this->size), this->size,(-1)*(this->size),
        this->size,(-1)*(this->size), this->size,
        (-1)*(this->size),(-1)*(this->size), this->size,
        (-1)*(this->size),(-1)*(this->size),(-1)*(this->size),
        (-1)*(this->size), this->size, this->size,
        (-1)*(this->size),(-1)*(this->size), this->size,
        this->size,(-1)*(this->size), this->size,
        this->size, this->size, this->size,
        this->size,(-1)*(this->size),(-1)*(this->size),
        this->size, this->size,(-1)*(this->size),
        this->size,(-1)*(this->size),(-1)*(this->size),
        this->size, this->size, this->size,
        this->size,(-1)*(this->size), this->size,
        this->size, this->size, this->size,
        this->size, this->size,(-1)*(this->size),
        (-1)*(this->size), this->size,(-1)*(this->size),
        this->size, this->size, this->size,
        (-1)*(this->size), this->size,(-1)*(this->size),
        (-1)*(this->size), this->size, this->size,
        this->size, this->size, this->size,
        (-1)*(this->size), this->size, this->size,
        this->size,(-1)*(this->size), this->size
    };

    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(this->size);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ball::set_position(glm::vec3 v) {
    this->position -= v;
}

void Ball::tick(int type) {
    // type is to differentiate between the different directions of the 2 balls 
     //this->rotation += speed;
    // this->position.x -= type*speed;
    //this->position.y -= type*speed;
}

