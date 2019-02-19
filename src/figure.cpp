#include "figure.h"
#include "main.h"


Sphere ::Sphere(float x, float y,float z,color_t color,float size) {
    this->position = glm::vec3(x, y, z);
    this->size = size;
    this->rotation = 0;
    this->n =20;
    this->m = 50;
       // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    //std::cout<<n<<"n \n";

    for(int i=0;i<this->m;i++)
    {
        float angle = i*(360/this->m);
        this->part[i] = Polygon(x,y,z,color,size,this->n,i*(360/this->m));
        //std::cout<<" rotation "<<this->part[i].rotation;
    }
    this->part[50] = Polygon(x,y,z,color,size,this->n,90);
}

void Sphere::draw(glm::mat4 VP) {
    for(int i=0;i<this->m;i++)
    {
        this->part[i].position = this->position;
        this->part[i].draw(VP,glm::vec3(0,1,0));
    }
    this->part[50].position = this->position;
    this->part[50].draw(VP,glm::vec3(1,0,0));
}

void Sphere::set_position(glm::vec3 v) {
    this->position -= v;
    for(int i=0;i<this->m;i++)
    {
        this->part[i].set_position(v);
    }
    this->part[50].set_position(v);
}

void Sphere::tick(int type) {
    // type is to differentiate between the different directions of the 2 balls 
     //this->rotation += type;
     //this->position.x -= type*speed;
    //this->position.y -= type*speed;
}

int Sphere::move(float x , float y,float z){

    this->position.x += x;
    this->position.y += y;
    this->position.z += z;
    // check if the item is within the boundaries of the screen ( += 10 all sides)
    return 0;
}

Semi ::Semi(float x, float y,float z,color_t color,float size,int n) {
    this->position = glm::vec3(x, y, z);
    this->size = size;
    this->rotation = 0;
       // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    std::cout<<n<<"n \n";
    GLfloat vertex_buffer_data[9*n] ;
    float angle = 180/n,c=1.0f,s=0;
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

void Semi::draw(glm::mat4 VP) {
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

void Semi::set_position(glm::vec3 v) {
    this->position -= v;
}

void Semi::tick(int type) {
    // type is to differentiate between the different directions of the 2 balls 
     //this->rotation += type;
     //this->position.x -= type*speed;
    //this->position.y -= type*speed;
}

int Semi::move(float x , float y,float z){

    this->position.x += x;
    this->position.y += y;
    this->position.z += z;
    // check if the item is within the boundaries of the screen ( += 10 all sides)
    return 0;
}