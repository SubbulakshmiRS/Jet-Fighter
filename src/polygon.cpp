#include "polygon.h"
#include "main.h"


Polygon ::Polygon(float x, float y,color_t color,float size,int n,float rotation) {
    this->position = glm::vec3(x, y, 0);
    this->size = size;
    this->rotation = rotation;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[9*n] ;
    float angle = 360/n,c=1.0f,s=0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<3;j++)
            vertex_buffer_data[9*i+j] = 0;

        vertex_buffer_data[9*i+3]= this->size*c;//i*angle;
        vertex_buffer_data[9*i+4]=this->size*s;
        vertex_buffer_data[9*i+5]=0;

        c=cos(((i+1)*angle*M_PI)/180);
        s=sin(((i+1)*angle*M_PI)/180);

        vertex_buffer_data[9*i+6]=this->size*c;//(i+1)*angle
        vertex_buffer_data[9*i+7]=this->size*s;
        vertex_buffer_data[9*i+8]=0;      
    }

    this->object = create3DObject(GL_TRIANGLES, 3*n, vertex_buffer_data, color, GL_FILL);
}

void Polygon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.5f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Polygon::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Polygon::tick(int type) {
    // type is to differentiate between the different directions of the 2 balls 
     //this->rotation += type;
     //this->position.x -= type*speed;
    //this->position.y -= type*speed;
}

int Polygon::move(float x , float y){

    this->position.x += x;
    this->position.y += y;
    // check if the item is within the boundaries of the screen ( += 10 all sides)
    return 0;
}
