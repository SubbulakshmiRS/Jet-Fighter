#include "plane.h"
#include "main.h"


Plane ::Plane(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
    this->rotate_vec = glm::vec3(1, 0, 0);
    this->rotation = 0;
    this->speed_x=this->speed_y = 0;
    int n =6;
    float x_pos = 1.0f,y_pos = 0;
    GLfloat vertex_buffer_data[3*9*n] ;

    float angle = 360/n,c=1.0f,s=0;
    for(int i=0;i<n;i++)
    {

        float a = (0.5f)*c,b=(0.5f)*s;

        vertex_buffer_data[18*i+0]= a;//i*angle;
        vertex_buffer_data[18*i+1]=b;
        vertex_buffer_data[18*i+2]=5.0f;

       /* vertex_buffer_data[18*i+18]= a;//i*angle;
        vertex_buffer_data[18*i+19]=b;
        vertex_buffer_data[18*i+20]=6.0f;*/

        vertex_buffer_data[18*i+9]= a;//i*angle;
        vertex_buffer_data[18*i+10]=b;
        vertex_buffer_data[18*i+11]=5.0f;

        vertex_buffer_data[18*i+12]= a;//i*angle;
        vertex_buffer_data[18*i+13]=b;
        vertex_buffer_data[18*i+14]=6.5f;

        c=cos(((i+1)*angle*M_PI)/180);
        s=sin(((i+1)*angle*M_PI)/180);

        a = (0.5f)*c;b=(0.5f)*s;

        vertex_buffer_data[18*i+3]= a;//(i+1)*angle;
        vertex_buffer_data[18*i+4]=b;
        vertex_buffer_data[18*i+5]=6.5f;  

       /* vertex_buffer_data[18*i+24]= a;//(i+1)*angle;
        vertex_buffer_data[18*i+25]=b;
        vertex_buffer_data[18*i+26]=6.0f;  */    

        vertex_buffer_data[18*i+6]= a;//(i+1)*angle;
        vertex_buffer_data[18*i+7]=b;
        vertex_buffer_data[18*i+8]=5.0f;   

        vertex_buffer_data[18*i+15]= a;//(i+1)*angle;
        vertex_buffer_data[18*i+16]=b;
        vertex_buffer_data[18*i+17]=6.5f;

       /* vertex_buffer_data[18*i+21]= 0;//snout;
        vertex_buffer_data[18*i+22]=0;
        vertex_buffer_data[18*i+23]=6.5f;   */
    
    }

    this->object = create3DObject(GL_TRIANGLES, 6*n, vertex_buffer_data,COLOR_DEAD_BLACK, GL_FILL);
    this->part1 = Polygon(0,0,5,COLOR_RED,0.5f,6,0);

    this->part2 = Polygon(0,0,6.5,COLOR_RED,0.5f,6,0);
}

void Plane::draw(glm::mat4 VP) {
    
    Matrices.model = glm::mat4(0.5f);

    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 translate1 = glm::translate (glm::vec3(0.0f,0.0f,-5.75f));    // glTranslatef
    glm::mat4 translate2 = glm::translate (glm::vec3(0.0f,0.0f,5.75f));    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), this->rotate_vec);
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate *translate2*rotate*translate1);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    glm::mat4 translate3 = glm::translate (glm::vec3(0.0f,0.0f,0.75f));
    glm::mat4 translate4 = glm::translate (glm::vec3(0.0f,0.0f,-0.75f));
    this->part1.draw1(VP,this->rotate_vec,(translate3*rotate*translate4));
    this->part2.draw1(VP,this->rotate_vec,(translate4*rotate*translate3));
}

void Plane::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void Plane::tick() {
    // type is to differentiate between the different directions of the 2 balls 
     //this->rotation += type;
     //this->position.x -= type*speed;
    this->position.y += this->speed_y;
    this->part1.position.y += this->speed_y;
    this->part2.position.y += this->speed_y;
    this->speed_y -= 0.0005f;
}

void Plane::tilt_left(){
    if (this->rotate_vec != glm::vec3(0,0,1))
        {
            this->rotation =0;
            this->part1.rotation = 0;
            this->part2.rotation = 0;
        }
    this->part1.rotation += 10;
    this->part2.rotation += 10;
    this->rotation += 10;
    this->rotate_vec = glm::vec3(0, 0, 1);
}

void Plane::tilt_right(){
    if (this->rotate_vec != glm::vec3(0,0,1))
        {
            this->rotation =0;
            this->part1.rotation = 0;
            this->part2.rotation = 0;
        }
    this->part1.rotation -= 10;
    this->part2.rotation -= 10;
    this->rotation -= 10;
    this->rotate_vec = glm::vec3(0, 0, 1);
}

void Plane::rotate_c(){
    if (this->rotate_vec != glm::vec3(0,1,0))
        {
            this->rotation =0;
            this->part1.rotation = 0;
            this->part2.rotation = 0;
        }
    this->part1.rotation += 1;
    this->part2.rotation += 1;
    this->rotation += 1;
    this->rotate_vec = glm::vec3(0, 1, 0);
}

void Plane::rotate_cc(){
    if (this->rotate_vec != glm::vec3(0,1,0))
        {
            this->rotation =0;
            this->part1.rotation = 0;
            this->part2.rotation = 0;
        }
    this->part1.rotation -= 1;
    this->part2.rotation -= 1;
    this->rotation -= 1;
    this->rotate_vec = glm::vec3(0, 1, 0);
}

int Plane::move(float x , float y,float z){

    this->position.x += x;
    this->position.y += y;
    // check if the item is within the boundaries of the screen ( += 10 all sides)
    return 0;
}
