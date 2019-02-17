#include "background.h"
#include "main.h"


Background ::Background(int scene) {
    //float x = 0,y=0,z=10.0f;
    this->position = glm::vec3(0,-10.0f,0);
    this->rotation = 0;
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
    for (std::vector<Island>::iterator it = this->islands.begin() ; it != this->islands.end(); ++it)
    {
        it->part1.draw(VP);
        it->part2.draw(VP);
        it->part3.draw(VP);
    }
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

void Background::create() {
    int r[] = {1,-1};
    int temp = rand()%2; temp = r[temp];
    Island t ;
    float x = this->position.x+2.0f,y=this->position.y,z=this->position.z+2;
    double step = (rand()%100);
    std::cout<<"\nstep "<<step;
    step = step/100;
    t.part1 = Ball(x+step,y+step,z+step,0.5,COLOR_BRIGHT_GREEN);
    step = (rand()%100);
    step = step/100;
    step *= temp;
    t.part2 = Ball(t.part1.position.x+step,t.part1.position.y+step,t.part1.position.z+step,0.7f,COLOR_GREEN);
    step = (rand()%100);
    step = step/100;
     t.part3 = Ball(t.part2.position.x+step,t.part2.position.y+step,t.part2.position.z+step,0.3f,COLOR_DARK_GREEN);
    t.position = t.part2.position;

    this->islands.push_back(t);

}

Volcano ::Volcano(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    float t = rand()%10; t=t/100;t+=0.05f;
    this->top = t;
    this->bottom = 0.3f;
    t=rand()%10; t= t/100; t+= 0.1f;
    this->height = t;
    int n =6;
    float x_pos = 1.0f,y_pos = 0;
    GLfloat vertex_buffer_data[2*9*n] ;

    float angle = 360/n,c=1.0f,s=0;
    for(int i=0;i<n;i++)
    {

        float a = (this->top)*c,b=(this->top)*s;
        float a1 = (this->bottom)*c,b1=(this->bottom)*s;

        vertex_buffer_data[18*i+0]= a;//i*angle;
        vertex_buffer_data[18*i+1]=0;
        vertex_buffer_data[18*i+2]=b;

        vertex_buffer_data[18*i+9]= a;//i*angle;
        vertex_buffer_data[18*i+10]=0;
        vertex_buffer_data[18*i+11]=b;

        vertex_buffer_data[18*i+12]= a1;//i*angle;
        vertex_buffer_data[18*i+13]=(-1)*this->height;
        vertex_buffer_data[18*i+14]=b1;

        c=cos(((i+1)*angle*M_PI)/180);
        s=sin(((i+1)*angle*M_PI)/180);

        a = (this->top)*c;b=(this->top)*s;
        a1 = (this->bottom)*c;b1=(this->bottom)*s;

        vertex_buffer_data[18*i+3]= a1;//(i+1)*angle;
        vertex_buffer_data[18*i+4]=(-1)*this->height;
        vertex_buffer_data[18*i+5]=b1;  

        vertex_buffer_data[18*i+6]= a;//(i+1)*angle;
        vertex_buffer_data[18*i+7]=0;
        vertex_buffer_data[18*i+8]=b;   

        vertex_buffer_data[18*i+15]=a1;//(i+1)*angle;
        vertex_buffer_data[18*i+16]=(-1)*this->height;
        vertex_buffer_data[18*i+17]=b1;
    
    }
    this->part1 = Polygon(0,0,0,COLOR_LIGHT_ORANGE,this->top-0.1f,n,0);
    this->part2 = Polygon(0,0,0,COLOR_RED,this->top-0.3f,n,0);
    this->object = create3DObject(GL_TRIANGLES, 6*n, vertex_buffer_data,COLOR_DEAD_BLACK, GL_FILL);

}

void Volcano::draw(glm::mat4 VP) {
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
    this->part1.draw(VP,glm::vec3(0,0,1)
    
    );
    this->part2.draw(VP,glm::vec3(0,0,1));
}

void Volcano::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void Volcano::tick(int type) {
    // type is to differentiate between the different directions of the 2 balls 
     //this->rotation += type;
     //this->position.x -= type*speed;
    //this->position.y -= type*speed;
}