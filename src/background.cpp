#include "background.h"
#include "main.h"

glm::vec3 cross_product(glm::vec3 a,glm::vec3 b)
{
    a = glm::normalize(a);
    b = glm::normalize(b);
    float u1=a.x, u2=a.y, u3=a.z, v1=b.x, v2=b.y, v3=b.z;
    float  uvi, uvj, uvk;
    
    uvi = u2 * v3 - v2 * u3;
    uvj = v1 * u3 - u1 * v3;
    uvk = u1 * v2 - v1 * u2;
    return glm::vec3(uvi,uvj,uvk);
}

float dot_product(glm::vec3 a,glm::vec3 b)
{
    a = glm::normalize(a);
    b = glm::normalize(b);
    float result = a.x*b.x + a.y*b.y + a.z*b.z;
    return result ;
}

float magnitude(glm::vec3 a)
{
    float r = a.x*a.x + a.y*a.y + a.z*a.z;
    float result = sqrt(r);
    return result;
}

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

    this->stat = 0;
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
        if(it->present)
            it->volcano.draw(VP);
    }
}

void Background::set_position(glm::vec3 v) {
    this->position -= v;
    for (std::vector<Island>::iterator it = this->islands.begin() ; it != this->islands.end(); ++it)
    {
        it->position -= v;
        it->part1.set_position(v);
        it->part2.set_position(v);
        it->part3.set_position(v);
        if(it->present)
            it->volcano.set_position(v);
    }
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

void Background::create(glm::vec3 v) {

    int r[] = {1,-1};
    int temp = rand()%2; temp = r[temp];
    Island t ;
    t.present = rand()%2;
    float x = v.x+2.0f+(rand()%10-4),y=this->position.y-0.29f,z=v.z+(rand()%10-2)+10;
    double step = (rand()%100);
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

    if(t.present)
        t.volcano = Volcano(t.part2.position.x,t.part2.position.y+0.7f,t.part2.position.z);

    this->stat++;
    this->islands.push_back(t);

}

void Background::delete_element(glm::vec3 p ){
    int i=0;
    if(this->stat <= 0)
        return ;
    for (std::vector<Island>::iterator it = this->islands.begin() ; it < this->islands.end(); ++it)
    {
        //std::cout<<i;
        float d1 = fabs(it->position.x-p.x) , d2 = fabs(it->position.z-p.z);
        //std::cout<<"d1 "<<d1<<" d2 "<<d2<<"\n";
        if (d1 > 20 || d2 > 20 )
        {
            this->islands.erase(it);
            this->stat--;
            std::cout<<"deleted \n";
        }
        i++;

    }
}

Volcano ::Volcano(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    float t = rand()%10; t=t/100;t+=0.2f;
    this->top = t;
    this->bottom = 0.5f;
    t=rand()%10; t= t/100; t+= 0.2f;
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
        vertex_buffer_data[18*i+1]=this->height;
        vertex_buffer_data[18*i+2]=b;

        vertex_buffer_data[18*i+9]= a;//i*angle;
        vertex_buffer_data[18*i+10]=this->height;
        vertex_buffer_data[18*i+11]=b;

        vertex_buffer_data[18*i+12]= a1;//i*angle;
        vertex_buffer_data[18*i+13]=0;
        vertex_buffer_data[18*i+14]=b1;

        c=cos(((i+1)*angle*M_PI)/180);
        s=sin(((i+1)*angle*M_PI)/180);

        a = (this->top)*c;b=(this->top)*s;
        a1 = (this->bottom)*c;b1=(this->bottom)*s;

        vertex_buffer_data[18*i+3]= a1;//(i+1)*angle;
        vertex_buffer_data[18*i+4]=0;
        vertex_buffer_data[18*i+5]=b1;  

        vertex_buffer_data[18*i+6]= a;//(i+1)*angle;
        vertex_buffer_data[18*i+7]=this->height;
        vertex_buffer_data[18*i+8]=b;   

        vertex_buffer_data[18*i+15]=a1;//(i+1)*angle;
        vertex_buffer_data[18*i+16]=0;
        vertex_buffer_data[18*i+17]=b1;
    
    }
    this->part1 = Polygon(x,this->height+y,z,COLOR_LIGHT_ORANGE,this->top,n,90);
    this->part2 = Polygon(x,this->height+y,z,COLOR_RED,this->top-0.3f,n,90);
    this->object = create3DObject(GL_TRIANGLES, 6*n, vertex_buffer_data,COLOR_BROWN, GL_FILL);

}

void Volcano::draw(glm::mat4 VP) {

    Matrices.model = glm::mat4(this->top);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    this->part1.draw(VP,glm::vec3(1,0,0));
    this->part2.draw(VP,glm::vec3(1,0,0));
}

void Volcano::set_position(glm::vec3 v) {
    this->position -= v;
    this->part1.set_position(v);
    this->part2.set_position(v);
}

void Volcano::tick(int type) {
    // type is to differentiate between the different directions of the 2 balls 
     //this->rotation += type;
     //this->position.x -= type*speed;
    //this->position.y -= type*speed;
}

Arrow ::Arrow(int scene) {
    this->position = glm::vec3(5,5,0);
    this->rotation = 0;
    this->align = glm::vec3(0,0,1);
    this->current_align = this->align;
    GLfloat vertex_buffer_data[] = {
        1.0f,0.2f,0,
        0,0.2f,1.0f,
        -1.0f,0.2f,0,
        0.3f,0.2f,0,
        -0.3f,0.2f,0,
        0.3f,0.2f,-1.5f,
        -0.3f,0.2f,0,
        -0.3f,0.2f,-1.5f,
        0.3f,0.2f,-1.5f, // top half 

       1.0f,-0.2f,0,
        0,-0.2f,1.5f,
        -1.0f,-0.2f,0,
        0.3f,-0.2f,0,
        -0.3f,-0.2f,0,
        0.3f,-0.2f,-1.5f,
        -0.3f,-0.2f,0,
        -0.3f,-0.2f,-1.5f,
        0.3f,-0.2f,-1.5f, // bottom half

        -0.3f,0.2f,-1.5f,
        -0.3f,-0.2f,-1.5f,
        0.3f,-0.2f,-1.5f,
        -0.3f,0.2f,-1.5f,
        0.3f,-0.2f,-1.5f,
        0.3f,0.2f,-1.5f, // rect 1

        0.3f,0.2f,-1.5f,
        0.3f,-0.2f,-1.5f,
        0.3f,-0.2f,0,
        0.3f,0.2f,-1.5f,
        0.3f,-0.2f,0,
        0.3f,0.2f,0, //rect 2

        -0.3f,0.2f,-1.5f,
        -0.3f,-0.2f,-1.5f,
        -0.3f,-0.2f,0,
        -0.3f,0.2f,-1.5f,
        -0.3f,-0.2f,0,
        -0.3f,0.2f,0, // rect 7

        0.3f,0.2f,0,
        0.3f,-0.2f,0,
        1.0f,-0.2f,0,
        0.3f,0.2f,0,
        1.0f,-0.2f,0,
        1.0f,0.2f,0, // rect 3

        -0.3f,0.2f,0,
        -0.3f,-0.2f,0,
        -1.0f,-0.2f,0,
        -0.3f,0.2f,0,
        -1.0f,-0.2f,0,
        -1.0f,0.2f,0,  // rect 6

        1.0f,0.2f,0,
        1.0f,-0.2f,0,
        0,-0.2f,1.0f,
        1.0f,0.2f,0,
        0,-0.2f,1.0f,
        0,0.2f,1.0f, // rect 4

        0,0.2f,1.0f,
        0,-0.2f,1.0f,
        -1.0f,-0.2f,0,
        0,0.2f,1.0f,
        -1.0f,-0.2f,0,
        -1.0f,0.2f,0, // rect 5 

    };
    int s = sizeof(vertex_buffer_data)/sizeof(vertex_buffer_data[0]);
    s = s/3;

    this->object = create3DObject(GL_TRIANGLES, s, vertex_buffer_data, COLOR_RED, GL_FILL);
}

void Arrow::draw(glm::mat4 VP,glm::vec3 direction) {
    //p is the checkpoint 
    glm::vec3 v = cross_product(this->align,direction);
    float s = magnitude(v);
    float c = dot_product(this->align,direction);

    float m[16]={
        0,(-1)*v.z,v.y,0,
        v.z,0,(-1)*v.x,0,
        (-1)*v.y,v.x,0,0,
        0,0,0,1,
    } ;

    float t = 1/(1+c);
    glm::mat4 vrot1 = glm::make_mat4(m);;
    glm::mat4 vrot = glm::transpose(vrot1);

    glm::mat4 result = glm::mat4(1.0f) + vrot + vrot*vrot*t ;

    Matrices.model = glm::mat4(0.5f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate * result);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    this->current_align = direction;
}

void Arrow::set_position(glm::vec3 v) {
    this->position -= v;
}

void Arrow::tick(int type) {
    // type is to differentiate between the different directions of the 2 balls 
     //this->rotation += type;
     //this->position.x -= type*speed;
    //this->position.y -= type*speed;
}

Checkpoint ::Checkpoint(float x,float z) {
    this->position = glm::vec3(x, -7, z);
    this->rotation = 0;
    this->align = glm::vec3(0,1,0);
    this->cur_align = this->align;
       // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    this->top = 0.5f;
    this->bottom = 1.0f;
    this->height = 3.0f;
    int n =10;
    float x_pos = 1.0f,y_pos = 0;
    GLfloat vertex_buffer_data[2*9*n] ;

    float angle = 360/n,c=1.0f,s=0;
    for(int i=0;i<n;i++)
    {

        float a = (this->top)*c,b=(this->top)*s;
        float a1 = (this->bottom)*c,b1=(this->bottom)*s;

        vertex_buffer_data[18*i+0]= a;//i*angle;
        vertex_buffer_data[18*i+1]=this->height;
        vertex_buffer_data[18*i+2]=b;

        vertex_buffer_data[18*i+9]= a;//i*angle;
        vertex_buffer_data[18*i+10]=this->height;
        vertex_buffer_data[18*i+11]=b;

        vertex_buffer_data[18*i+12]= a1;//i*angle;
        vertex_buffer_data[18*i+13]=0;
        vertex_buffer_data[18*i+14]=b1;

        c=cos(((i+1)*angle*M_PI)/180);
        s=sin(((i+1)*angle*M_PI)/180);

        a = (this->top)*c;b=(this->top)*s;
        a1 = (this->bottom)*c;b1=(this->bottom)*s;

        vertex_buffer_data[18*i+3]= a1;//(i+1)*angle;
        vertex_buffer_data[18*i+4]=0;
        vertex_buffer_data[18*i+5]=b1;  

        vertex_buffer_data[18*i+6]= a;//(i+1)*angle;
        vertex_buffer_data[18*i+7]=this->height;
        vertex_buffer_data[18*i+8]=b;   

        vertex_buffer_data[18*i+15]=a1;//(i+1)*angle;
        vertex_buffer_data[18*i+16]=0;
        vertex_buffer_data[18*i+17]=b1;
    
    }

    this->object = create3DObject(GL_TRIANGLES, 6*n, vertex_buffer_data,COLOR_SMOKE, GL_FILL);
    this->platform = Ball(this->position.x,this->position.y-2.5f,this->position.z,1.5f,COLOR_BROWN);
    this->part1 = Sphere(this->position.x,this->position.y,this->position.z,COLOR_DEAD_BLACK,0.75f);
}

void Checkpoint::draw(glm::mat4 VP,glm::vec3 p) {
    
    glm::vec3 direction = p - this->position ;
    glm::vec3 v = cross_product(this->align,direction);
    float s = magnitude(v);
    float c = dot_product(this->align,direction);

    float m[16]={
        0,(-1)*v.z,v.y,0,
        v.z,0,(-1)*v.x,0,
        (-1)*v.y,v.x,0,0,
        0,0,0,1,
    } ;

    float t = 1/(1+c);
    glm::mat4 vrot1 = glm::make_mat4(m);;
    glm::mat4 vrot = glm::transpose(vrot1);

    glm::mat4 result = glm::mat4(1.0f) + vrot + vrot*vrot*t ;

    Matrices.model = glm::mat4(0.5f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * result);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    this->part1.draw(VP);
    this->platform.draw(VP);
    this->cur_align = direction;
    std::vector<Cannon>::iterator it;
    for (it=this->cannons.begin(); it<(this->cannons.end()); it++)
    {
        it->b.draw(VP);
    }

}

void Checkpoint::set_position(glm::vec3 v) {
    this->position -= v;
    this->platform.set_position(v);
    this->part1.set_position(v);
    std::vector<Cannon>::iterator it;
    for (it=this->cannons.begin(); it<(this->cannons.end()); it++)
    {
        it->b.set_position(v);
    }
}

void Checkpoint::tick() {
    std::vector<Cannon>::iterator it;
    for (it=this->cannons.begin(); it<(this->cannons.end()); it++)
    {
        it->b.position += it->velocity;
    }
}

int Checkpoint::move(float x , float y,float z){

    this->position.x += x;
    this->position.y += y;
    this->position.z += z;
    // check if the item is within the boundaries of the screen ( += 10 all sides)
    return 0;
}

void Checkpoint::shoot()
{
    Cannon temp ;
    glm::vec3 a = glm::normalize(this->cur_align);
   temp.velocity.x = a.x*(0.015f);
    temp.velocity.y = a.y*(0.015f);
    temp.velocity.z = a.z*(0.015f);
    temp.b = Ball(this->position.x,this->position.y,this->position.z,0.1f,COLOR_DEAD_BLACK);
    this->cannons.push_back(temp);

}