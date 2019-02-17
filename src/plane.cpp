#include "plane.h"
#include "main.h"


Plane ::Plane(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
    this->rotate_vec = glm::vec3(1, 0, 0);
    this->rotation = 0;
    this->speed_x=this->speed_y = 0;
    int n =6;
    float x_pos = 1.0f,y_pos = 0;
    GLfloat vertex_buffer_data[2*9*n +9*3 + 18*n] ;

    float angle = 360/n,c=1.0f,s=0;
    for(int i=0;i<n;i++)
    {

        float a = (0.5f)*c,b=(0.5f)*s;

        vertex_buffer_data[18*i+0]= a;//i*angle;
        vertex_buffer_data[18*i+1]=b;
        vertex_buffer_data[18*i+2]=5.0f;

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

        vertex_buffer_data[18*i+6]= a;//(i+1)*angle;
        vertex_buffer_data[18*i+7]=b;
        vertex_buffer_data[18*i+8]=5.0f;   

        vertex_buffer_data[18*i+15]= a;//(i+1)*angle;
        vertex_buffer_data[18*i+16]=b;
        vertex_buffer_data[18*i+17]=6.5f;
    
    }

    angle = 360/n;c=1.0f;s=0;
    for(int i = 0;i<3;i++)
    {
        float  a = (0.5f)*c,b=(0.5f)*s;
        vertex_buffer_data[18*n+9*i] = a;
        vertex_buffer_data[18*n+9*i+1] = b;
        vertex_buffer_data[18*n+9*i+2] = 6.5f;
        
        a = (-0.5f)*c;b=(-0.5f)*s;
        vertex_buffer_data[18*n+9*i+3] = a;
        vertex_buffer_data[18*n+9*i+4] = b;
        vertex_buffer_data[18*n+9*i+5] = 6.5f;

        vertex_buffer_data[18*n+9*i+6] = 0;
        vertex_buffer_data[18*n+9*i+7] = 0;
        vertex_buffer_data[18*n+9*i+8] = 7.0f;

        c=cos(((i+1)*angle*M_PI)/180);
        s=sin(((i+1)*angle*M_PI)/180);

    }

    angle = 360/n;c=1.0f;s=0;
    for(int i=0;i<n;i++)
    {

        float a = (0.3f)*c,b=(0.3f)*s+0.7f;

        vertex_buffer_data[18*n+27+18*i+0]= a;//i*angle;
        vertex_buffer_data[18*n+27+18*i+1]=b;
        vertex_buffer_data[18*n+27+18*i+2]=5.2f;

        vertex_buffer_data[18*n+27+18*i+9]= a;//i*angle;
        vertex_buffer_data[18*n+27+18*i+10]=b;
        vertex_buffer_data[18*n+27+18*i+11]=5.2f;

        vertex_buffer_data[18*n+27+18*i+12]= a;//i*angle;
        vertex_buffer_data[18*n+27+18*i+13]=b;
        vertex_buffer_data[18*n+27+18*i+14]=5.7f;

        c=cos(((i+1)*angle*M_PI)/180);
        s=sin(((i+1)*angle*M_PI)/180);

        a = (0.3f)*c;b=(0.3f)*s+0.7f;

        vertex_buffer_data[18*n+27+18*i+3]= a;//(i+1)*angle;
        vertex_buffer_data[18*n+27+18*i+4]=b;
        vertex_buffer_data[18*n+27+18*i+5]=5.7f;   

        vertex_buffer_data[18*n+27+18*i+6]= a;//(i+1)*angle;
        vertex_buffer_data[18*n+27+18*i+7]=b;
        vertex_buffer_data[18*n+27+18*i+8]=5.2f;   

        vertex_buffer_data[18*n+27+18*i+15]= a;//(i+1)*angle;
        vertex_buffer_data[18*n+27+18*i+16]=b;
        vertex_buffer_data[18*n+27+18*i+17]=5.7f;
    }    


    this->object = create3DObject(GL_TRIANGLES, 12*n+9, vertex_buffer_data,COLOR_DEAD_BLACK, GL_FILL);
    this->part1 = Polygon(0,0,5,COLOR_RED,0.5f,6,0);
    this->part2 = Polygon(0,0,6.5,COLOR_RED,0.5f,6,0);
    this->part3 = Polygon(0,0,5.2f,COLOR_BRIGHT_GREEN,0.3f,6,0);
    this->part4 = Polygon(0,0,5.7f,COLOR_BRIGHT_GREEN,0.3f,6,0);
}

void Plane::draw(glm::mat4 VP) {
    
    Matrices.model = glm::mat4(0.5f);

    glm::mat4 d1 = glm::translate (this->position+glm::vec3(0,0,5));
    glm::mat4 d2 = glm::translate (this->position+glm::vec3(0,0,6.5f));

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
    glm::mat4 translate5 = glm::translate (glm::vec3(0.0f,0.0f,0.05f));    // glTranslatef
    glm::mat4 translate6 = glm::translate (glm::vec3(0.0f,0.7f,-0.05f));    // glTranslatef    
    glm::mat4 translate7 = glm::translate (glm::vec3(0.0f,0.0f,0.55f));    // glTranslatef
    glm::mat4 translate8 = glm::translate (glm::vec3(0.0f,0.7f,-0.55f));    // glTranslatef  

    this->part1.draw2(VP,(translate3*d1*rotate*translate4));
    this->part2.draw2(VP,(translate4*d2*rotate*translate3));
    this->part3.draw1(VP,this->rotate_vec,(translate7*rotate*translate8));
    this->part4.draw1(VP,this->rotate_vec,(translate5*rotate*translate6));

    std::vector<Bullet>::iterator it;
    for (it=this->bullets.begin(); it<(this->bullets.end()); it++)
    {
        it->b.draw(VP);
    }
    std::vector<Bomb>::iterator it2;
    for (it2=this->bombs.begin(); it2<(this->bombs.end()); it2++)
    {
        it2->b.draw(VP);
    }

}

void Plane::set_position(glm::vec3 v) {
    this->position -= v;
    this->part1.set_position(v);
    this->part2.set_position(v);
    this->part3.set_position(v);
    this->part4.set_position(v);
}

void Plane::tick() {
    /*this->position.y += this->speed_y;
    this->part1.position.y += this->speed_y;
    this->part2.position.y += this->speed_y;
    this->speed_y -= 0.0005f;*/

    std::vector<Bullet>::iterator it;
    for (it=this->bullets.begin(); it<(this->bullets.end()); it++)
    {
        it->b.position.x += (it->velocity.x)*(1/100);
        it->b.position.y += (it->velocity.y)*(1/100);
        it->b.position.z += (it->velocity.z)*(1/100);
    }
    std::vector<Bomb>::iterator it2;
    for (it2=this->bombs.begin(); it2<(this->bombs.end()); it2++)
    {
        it2->b.position.x += (it2->velocityh.x)*(1/100);
        it2->b.position.y += (it2->velocityh.y)*(1/100);
        it2->b.position.z += (it2->velocityh.z)*(1/100);
        it2->b.position.z += it2->velocityv;
    }
}

void Plane::tilt_left(){
    if (this->rotate_vec != glm::vec3(0,0,1))
        {
            this->rotation =0;
            this->part1.rotation = 0;
            this->part2.rotation = 0;
            this->part3.rotation = 0;
            this->part4.rotation = 0;
        }
    this->part1.rotation += 10;
    this->part2.rotation += 10;
    this->part3.rotation += 10;
    this->part4.rotation += 10;
    this->rotation += 10;
    this->rotate_vec = glm::vec3(0, 0, 1);
}

void Plane::tilt_right(){
    if (this->rotate_vec != glm::vec3(0,0,1))
        {
            this->rotation =0;
            this->part1.rotation = 0;
            this->part2.rotation = 0;
            this->part3.rotation = 0;
            this->part4.rotation = 0;
        }
    this->part1.rotation -= 10;
    this->part2.rotation -= 10;
    this->part3.rotation -= 10;
    this->part4.rotation -= 10;
    this->rotation -= 10;
    this->rotate_vec = glm::vec3(0, 0, 1);
}

void Plane::rotate_c(){
    if (this->rotate_vec != glm::vec3(0,1,0))
        {
            this->rotation =0;
            this->part1.rotation = 0;
            this->part2.rotation = 0;
            this->part3.rotation = 0;
            this->part4.rotation = 0;
        }
    this->part1.rotation += 1;
    this->part2.rotation += 1;
    this->part3.rotation += 1;
    this->part4.rotation += 1;
    this->rotation += 1;
    float c =cos(this->rotation),s=sin(this->rotation);
    glm::vec3 m = glm::vec3((0.75*s),0,(0.75*c));
    glm::vec3 n = glm::vec3(((-0.75)*s),0,((-0.75)*c));
    n += glm::vec3(0,0,5.75f);
    m += glm::vec3(0,0,5.75f);
    
    this->part1.position = n;
    this->part2.position = m; 
    this->rotate_vec = glm::vec3(0, 1, 0);
}

void Plane::rotate_cc(){
    if (this->rotate_vec != glm::vec3(0,1,0))
        {
            this->rotation =0;
            this->part1.rotation = 0;
            this->part2.rotation = 0;
            this->part3.rotation = 0;
            this->part4.rotation = 0;
        }
    this->part1.rotation -= 1;
    this->part2.rotation -= 1;
    this->part3.rotation -= 1;
    this->part4.rotation -= 1;
    this->rotation -= 1;
    float c =cos(this->rotation),s=sin(this->rotation);
    glm::vec3 m = glm::vec3((0.75*s),0,(0.75*c));
    glm::vec3 n = glm::vec3(((-0.75)*s),0,((-0.75)*c));
    n += glm::vec3(0,0,5.75f);
    m += glm::vec3(0,0,5.75f);

    this->part1.position = n;
    this->part2.position = m; 
    this->rotate_vec = glm::vec3(0, 1, 0);
}

void Plane::shoot(int type)
{
    if(type == 1)
    {
        Bullet temp ;
        temp.velocity = (this->part1.position - this->part2.position);
        temp.b = Ball(this->position.x,this->position.y-0.7f,this->position.z,0.1f,COLOR_RED);
        this->bullets.push_back(temp);
    }
    if(type == 2)
    {
        Bomb temp ;
        temp.velocityh = (this->part1.position - this->part2.position);
        temp.velocityv = 0;
        temp.b = Ball(this->position.x,this->position.y-1,this->position.z,0.1f,COLOR_PINK);
        this->bombs.push_back(temp);
    }

    
}

int Plane::move(float x , float y,float z){

    this->position.x += x;
    this->position.y += y;
    // check if the item is within the boundaries of the screen ( += 10 all sides)
    return 0;
}
