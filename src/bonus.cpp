#include "bonus.h"
#include "main.h"


Ring ::Ring(float x, float y,float z,glm::vec3 rvec) {
    this->position = glm::vec3(x, y, z);
    this->size = 1.5f;
    this->rotation = 0;
    this->rvec = rvec;
       // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    int n=30;
    GLfloat vertex_buffer_data[9*n] ;
    float angle = 360/n,c=1.0f,s=0;
    float half = angle/2,hc=1.0f,hs=0;
    for(int i=0;i<n;i++)
    {
        hc=cos(((i*angle+half)*M_PI)/180);
        hs=sin(((i*angle+half)*M_PI)/180);

        vertex_buffer_data[9*i]= (0.75f)*this->size*hc;//i*angle;
        vertex_buffer_data[9*i+1]=(0.75f)*this->size*hs;
        vertex_buffer_data[9*i+2]=0;

        vertex_buffer_data[9*i+3]= this->size*c;//i*angle;
        vertex_buffer_data[9*i+4]=this->size*s;
        vertex_buffer_data[9*i+5]=0;

        c=cos(((i+1)*angle*M_PI)/180);
        s=sin(((i+1)*angle*M_PI)/180);

        vertex_buffer_data[9*i+6]=this->size*c;//(i+1)*angle
        vertex_buffer_data[9*i+7]=this->size*s;
        vertex_buffer_data[9*i+8]=0;      
    }

    this->object = create3DObject(GL_TRIANGLES, 3*n, vertex_buffer_data, COLOR_SMOKE, GL_FILL);
}

void Ring::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.5f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), this->rvec);
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ring::set_position(glm::vec3 v) {
    this->position -= v;
}

void Ring::tick() {
    this->rotation += 10;
}

int Ring::move(float x , float y,float z){

    this->position.x += x;
    this->position.y += y;
    this->position.z += z;
    // check if the item is within the boundaries of the screen ( += 10 all sides)
    return 0;
}
