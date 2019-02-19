#include "main.h"
#include "timer.h"
#include "ball.h"
#include "plane.h"
#include "background.h"
#include "dashboard.h"
#include "figure.h"
#include "bonus.h"
#include "enemy.h"

using namespace std;

GLMatrices Matrices,dummy;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/
int pressl,pressr ;
double cur_x_pos,cur_y_pos;
int type;
double add_x,add_y,add_z;
int t;
float theta,phi;
Ball ball1;
Ball ball2;
int stop;
Plane plane;
Background background;
Dashboard dashboard;
//Semi sm;
Ring ring;
Arrow arrow ;
Checkpoint checkpoint;
int checknum;
Fuel fuel ;
std::vector<Parachute> parachute;
int parachute_num;

float screen_zoom = 0.5, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

Timer t60(1.0 / 60);

void set_position(glm::vec3 v)
{
    background.set_position(v);
    for (std::vector<Parachute>::iterator it = parachute.begin() ; it < parachute.end(); ++it)
    {
        it->set_position(v);
    }
    checkpoint.set_position(v);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        plane.shoot(1);
    else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
        plane.shoot(2);
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    if(cur_x_pos == -1 && cur_y_pos == -1)
    {
    cur_x_pos = xpos;
    cur_y_pos = ypos;
    return;
    }

    if(type == 4)
    {
        if(xpos > cur_x_pos)
        {
            cout<<"right\n";
            add_x += 0.2f;
        }
        
        if(xpos < cur_x_pos)
        {
            cout<<"left\n";
            add_x -= 0.2f;
        }
        
        if(ypos < cur_y_pos)
        {
            cout<<"up\n";
            add_y += 0.2f;
        }

        if(ypos > cur_y_pos)
        {
            cout<<"down\n";
            add_y -= 0.2f;
        }

    }

    cur_x_pos = xpos;
    cur_y_pos = ypos;
    //cout<<xpos<<" : "<<ypos<<"\n";

}  

void delete_element_parachute(glm::vec3 p ){
    if(parachute_num <= 0)
        return ;
    for (std::vector<Parachute>::iterator it = parachute.begin() ; it < parachute.end(); ++it)
    {
        if (it->position.y <= -15)
        {
            parachute.erase(it);
            parachute_num--;
            std::cout<<"deleted \n";
        }
    }
}

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    int views[7][3][3] = {
        {{0,0,7},{0,0,10},{0,1,0}}, // plane view
        {{0,5,5.5f},{0,-10,5.5f},{0,0,1}}, // top view 
        {{0,5,0},{0,0,5.5f},{0,1,0}}, // follow cam view 
        {{10,10,-10},{0,0,5.5f},{0,0,1}}, // tower view 
        {{0,5,0},{0,0,5.5f},{0,1,0}} ,// helicopter view starting 
        {{0,0,5},{0,0,0},{0,1,0}},
        {{0,0,0},{0,0,5.5f},{0,1,0}} // back view
    };
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
   
    //glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    //glm::vec3 eye ( 3*sin(theta)*cos(phi),3*sin(theta)*sin(phi),3*cos(theta)*t );
    glm::vec3 eye ( views[type][0][0]+add_x,views[type][0][1]+add_y,views[type][0][2]+add_z);
    glm::vec3 target ( views[type][1][0],views[type][1][1],views[type][1][2]);
    glm::vec3 up (views[type][2][0],views[type][2][1],views[type][2][2]);

    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    glm::vec3 eye_dummy ( 0,0,5 );
    glm::vec3 target_dummy (0, 0, 0);
    glm::vec3 up_dummy (0, 1, 0);
    dummy.view = glm::lookAt(eye_dummy,target_dummy,up_dummy);
    glm::mat4 VP_dummy = Matrices.projection*dummy.view;

    glm::mat4 VP = Matrices.projection * Matrices.view;

    glm::mat4 MVP;  // MVP = Projection * View * Model

    plane.draw(VP);
    background.draw(VP);
    for (std::vector<Parachute>::iterator it = parachute.begin() ; it < parachute.end(); ++it)
    {
        it->draw(VP);
    }
    fuel.draw(VP_dummy);
    //sm.draw(VP_dummy);
    arrow.draw(VP_dummy,checkpoint.position - (plane.position + glm::vec3(0,0,5.75f)));
    checkpoint.draw(VP,plane.position+glm::vec3(0,0,5.75f));
    dashboard.draw(VP_dummy); // dashboard not viewable 
    //ring.draw(VP);
   //sphere.draw(VP);
}

void tick_input(GLFWwindow *window) {
    //int left = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) , right = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
    int one = glfwGetKey(window, GLFW_KEY_1) , two = glfwGetKey(window, GLFW_KEY_2),three = glfwGetKey(window, GLFW_KEY_3);
    int four = glfwGetKey(window, GLFW_KEY_4),five = glfwGetKey(window, GLFW_KEY_5),six = glfwGetKey(window, GLFW_KEY_6); 
    int seven = glfwGetKey(window, GLFW_KEY_7);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    int w = glfwGetKey(window, GLFW_KEY_W);
    int a = glfwGetKey(window, GLFW_KEY_A);
    int d = glfwGetKey(window, GLFW_KEY_D);
    int f = glfwGetKey(window, GLFW_KEY_F) , e = glfwGetKey(window, GLFW_KEY_E);
    int create = glfwGetKey(window, GLFW_KEY_C);

    int b = glfwGetKey(window, GLFW_KEY_B) , m = glfwGetKey(window, GLFW_KEY_M); // bomb and missle , temporary 

    int up  = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int forward = glfwGetKey(window, GLFW_KEY_ENTER);
    /*
    int up  = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int f = glfwGetKey(window, GLFW_KEY_F);*/

    if(one){ type = 0; add_x = add_y = add_z = 0;}
    else if (two) { type = 1;add_x = add_y = add_z = 0;}
    else if(three) {type = 2;add_x = add_y = add_z = 0;}
    else if(four) { type = 3;add_x = add_y = add_z = 0;}
    else if(five) { type = 4;}
    else if(six) { type = 5;add_x = add_y = add_z = 0;}
    else if(seven) { type = 6;add_x = add_y = add_z = 0;}

    if(space)
        plane.speed_y += 0.0001f;
    else if(w)
        plane.speed_x += 0.0001f;
    else if(a)
        plane.tilt_left();
    else if(d)
        plane.tilt_right();
    else if(f)
        plane.rotate_cc(); 
    else if(e)
        plane.rotate_c();

    if(up)
    {
        glm::vec3 v = glm::vec3(0,0.1f,0);
        set_position(v);    
    }
    if(down)
    {
        glm::vec3 v = glm::vec3(0,-0.1f,0);
        set_position(v);
    }
    if(forward)
    {
        pressl++;
        if (pressl == 4)
        {
        glm::vec3 v = plane.part1.position - plane.part2.position;
         v=  glm::normalize(v);
        pressl = 0;
        plane.speed_x += (float)((v.x)/500);
        plane.speed_y += (float)((v.y)/500);
        plane.speed_z += (float)((v.z)/500);
        }
    }
    if(create)
    {
        pressr++;
        if(pressr == 5)
        {
        background.create(plane.position);
        pressr = 0;
        }
    }

    if(b)
        plane.shoot(2);
    if(m)
        plane.shoot(1);

}

void tick_elements() {
    ring.tick();
    plane.tick();
    for (std::vector<Parachute>::iterator it = parachute.begin() ; it < parachute.end(); ++it)
    {
        it->tick();
    }

    glm::vec3 v = glm::vec3(plane.speed_x,plane.speed_y,plane.speed_z);
    set_position(v);

    float a = plane.position.y - background.position.y - 10;
    float t = (-1)*((a/10)*90.0f);
    if (t > -90.0f && t < 90.0f)
        dashboard.rotation = t;

    background.delete_element(plane.position);
    
    if(background.stat < 3)
    {
        while(background.stat<3)
        {
            glm::vec3 v = plane.part1.position - plane.part2.position;
            background.create(plane.position + v);
        }
    }

    delete_element_parachute(plane.position);
    if(parachute_num < 3)
    {
        while(parachute_num<3)
        {
            glm::vec3 v = plane.part1.position - plane.part2.position;
            Parachute t = create_parachute(plane.position + v);
            parachute.push_back(t);
            parachute_num++;
        }
    }

    // for no flying zone recognition;
    for (std::vector<Island>::iterator it = background.islands.begin() ; it != background.islands.end(); ++it)
    {
        //std::cout<<i;
        if (it->present)
        {
            float d1 = fabs(it->position.x-plane.position.x) , d2 = fabs(it->position.z-(plane.position.z+5.5));
            if (d1 < 0.3f || d2 < 0.3f )
            {
                cout<<"no flying zone";
            }
        }
    }

    // reaching a checkpoint
    float d1 = fabs(checkpoint.position.x-plane.position.x) , d2 = fabs(checkpoint.position.z-(plane.position.z+5.5));
    if (d1 < 0.3f || d2 < 0.3f )
    {
        checknum++;
        cout<<"\nCHECKPOINT REACHED\t"<<checknum<<"\n";
        sleep(10);
        float x = checkpoint.position.x,z=checkpoint.position.z;
        x -= rand()%5 + 10;
        z += rand()%5 ;
        z += 10;
        checkpoint = Checkpoint(x,z);
    }
    
    //cout<<"tick";
    //ball1.tick(stop*(-1));
    //ball2.tick(stop*1);
   /* bounding_box_t b1,b2;
    b1.x = ball1.position.x;
    b2.x = ball2.position.x;
    b1.y = ball1.position.y;
    b2.y = ball2.position.y;
    b1.width = b2.width = 0.5;
    b1.height = b2.height = 0.5;
    if (detect_collision(b1,b2))
    {
        //stop = 0; // to stop when once collided 
         stop = -1; // to return in the opposite directions 
    }*/
    // camera_rotation_angle += 1;
}

void initGL(GLFWwindow *window, int width, int height) {

    ball1       = Ball(-0.5f, 0,0,0.5f, COLOR_RED);
    ball2       = Ball(0, 0, 10,0.5f,COLOR_GREEN);
    plane = Plane(0,0,0);
    background = Background(1);
    dashboard = Dashboard(1);
    arrow = Arrow(1);
    checkpoint = Checkpoint(-5,5);
    fuel = Fuel(1);
    //sphere = Sphere(0,0,10,COLOR_GREEN,1.0f);

    //sm = Semi(0,0,0,COLOR_DEAD_BLACK,1.0f,10);
    glm::vec3 v = plane.part2.position - plane.part1.position;
    v=  glm::normalize(v);
    v+= plane.position;
    v.z += 10.0f;
    //cout<<"v.x "<<v.x<<"v.y "<<v.y<<"v.z "<<v.z<<"\n";
    ring = Ring(v.x,v.y,v.z,v);

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    checknum = 0;
    parachute_num = 0;
    pressl = pressr = 0;
    cur_x_pos = cur_y_pos = -1;
    add_x = add_y = add_z = 0;
    type = 0;
    theta = phi = 0;
    t=1;
    stop = 1;
    srand(time(0));
    int width  = 600;
    int height = 600;

    window = initGLFW(width, height);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
