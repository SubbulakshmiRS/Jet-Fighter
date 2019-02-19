#include "enemy.h"
#include "main.h"


Rope ::Rope(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[] = {
        (-1)*(0.075f),(-1)*(0.075f),(-1)*(0.075f), // triangle 1 : begin
        (-1)*(0.075f),(-1)*(0.075f), 0.075f,
        (-1)*(0.075f), 0.075f, 0.075f, // triangle 1 : end
        0.075f, 0.075f,(-1)*(0.075f), // triangle 2 : begin
        (-1)*(0.075f),(-1)*(0.075f),(-1)*(0.075f),
        (-1)*(0.075f), 0.075f,(-1)*(0.075f), // triangle 2 : end
        0.075f,(-1)*(0.075f), 0.075f,
        (-1)*(0.075f),(-1)*(0.075f),(-1)*(0.075f),
        0.075f,(-1)*(0.075f),(-1)*(0.075f),
        0.075f, 0.075f,(-1)*(0.075f),
        0.075f,(-1)*(0.075f),(-1)*(0.075f),
        (-1)*(0.075f),(-1)*(0.075f),(-1)*(0.075f),
        (-1)*(0.075f),(-1)*(0.075f),(-1)*(0.075f),
        (-1)*(0.075f), 0.075f, 0.075f,
        (-1)*(0.075f), 0.075f,(-1)*(0.075f),
        0.075f,(-1)*(0.075f), 0.075f,
        (-1)*(0.075f),(-1)*(0.075f), 0.075f,
        (-1)*(0.075f),(-1)*(0.075f),(-1)*(0.075f),
        (-1)*(0.075f), 0.075f, 0.075f,
        (-1)*(0.075f),(-1)*(0.075f), 0.075f,
        0.075f,(-1)*(0.075f), 0.075f,
        0.075f, 0.075f, 0.075f,
        0.075f,(-1)*(0.075f),(-1)*(0.075f),
        0.075f, 0.075f,(-1)*(0.075f),
        0.075f,(-1)*(0.075f),(-1)*(0.075f),
        0.075f, 0.075f, 0.075f,
        0.075f,(-1)*(0.075f), 0.075f,
        0.075f, 0.075f, 0.075f,
        0.075f, 0.075f,(-1)*(0.075f),
        (-1)*(0.075f), 0.075f,(-1)*(0.075f),
        0.075f, 0.075f, 0.075f,
        (-1)*(0.075f), 0.075f,(-1)*(0.075f),
        (-1)*(0.075f), 0.075f, 0.075f,
        0.075f, 0.075f, 0.075f,
        (-1)*(0.075f), 0.075f, 0.075f,
        0.075f,(-1)*(0.075f), 0.075f
    };

    int s = sizeof(vertex_buffer_data)/sizeof(vertex_buffer_data[0]);
    for(int i=0;i<s;i++)
    {
        if(i%3 == 1)
            vertex_buffer_data[i] *= 5;
    }
    
    s = (int) s/3;
    this->object = create3DObject(GL_TRIANGLES,s, vertex_buffer_data, COLOR_DEAD_BLACK, GL_FILL);
}

void Rope::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.5f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0,1,0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Rope::set_position(glm::vec3 v) {
    this->position -= v;
}

void Rope::tick(int type) {
    // type is to differentiate between the different directions of the 2 balls 
     //this->rotation += type;
     //this->position.x -= type*speed;
    //this->position.y -= type*speed;
}

int Rope::move(float x , float y,float z){

    this->position.x += x;
    this->position.y += y;
    this->position.z += z;
    // check if the item is within the boundaries of the screen ( += 10 all sides)
    return 0;
}


Parachute ::Parachute(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = rotation;

    this->balloon = Sphere(this->position.x,this->position.y,this->position.z,COLOR_INDIGO,1.5f);
    this->box = Ball(this->position.x,this->position.y-2.5f,this->position.z,0.5f,COLOR_BROWN);
    this->rope[0] = Rope(this->position.x-0.5f,this->position.y-1.75f,this->position.z+0.5f);
    this->rope[1] = Rope(this->position.x-0.5f,this->position.y-1.75f,this->position.z-0.5f);
    this->rope[2] = Rope(this->position.x+0.5f,this->position.y-1.75f,this->position.z+0.5f);
    this->rope[3] = Rope(this->position.x+0.5f,this->position.y-1.75f,this->position.z-0.5f);

}

void Parachute::draw(glm::mat4 VP) {
    this->balloon.draw(VP);
    this->box.draw(VP);
    for(int i=0;i<4;i++)
        this->rope[i].draw(VP);
}

void Parachute::set_position(glm::vec3 v) {
    this->position -= v;
    this->balloon.set_position(v);
    this->box.set_position(v);
    for(int i=0;i<4;i++)
        this->rope[i].set_position(v); 
}

void Parachute::tick() {

    this->position.y -= 0.005f;
    this->balloon.position.y -= 0.005f;
    this->box.position.y -= 0.005f;
    for(int i=0;i<4;i++)
        this->rope[i].position.y -= 0.005f;
    // type is to differentiate between the different directions of the 2 balls 
     //this->rotation += type;
     //this->position.x -= type*speed;
    //this->position.y -= type*speed;
}

int Parachute::move(float x , float y,float z){

    this->position.x += x;
    this->position.y += y;
    this->position.z += z;
    // check if the item is within the boundaries of the screen ( += 10 all sides)
    return 0;
}

Parachute create_parachute(glm::vec3 v) {

    int r[] = {1,-1};
    int temp = rand()%2; temp = r[temp];
    Parachute t;
    float x = v.x+2.0f+(rand()%10-4),y=7+(rand()%5),z=v.z+(rand()%10-2)+10;
    x *= temp;
    temp = rand()%2; temp = r[temp];
    z *= temp;
    t = Parachute(x,y,z);
    return t;
}
