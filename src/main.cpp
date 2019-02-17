#include "main.h"
#include "timer.h"
#include "ball.h"
#include "plane.h"
#include "background.h"
#include "dashboard.h"
#include "figure.h"
#include "bonus.h"

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
//Sphere sphere ;

float screen_zoom = 0.5, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

Timer t60(1.0 / 60);

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        plane.shoot(2);
    else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
        cout<<"right clicked\n";
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
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target ( views[type][1][0],views[type][1][1],views[type][1][2]);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (views[type][2][0],views[type][2][1],views[type][2][2]);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
        glm::vec3 eye_dummy ( 0,0,5 );
        glm::vec3 target_dummy (0, 0, 0);
        glm::vec3 up_dummy (0, 1, 0);
        dummy.view = glm::lookAt(eye_dummy,target_dummy,up_dummy);
        glm::mat4 VP_dummy = Matrices.projection*dummy.view;
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, -3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    /*ball1.draw(VP);
    ball2.draw(VP);*/
    plane.draw(VP);
    background.draw(VP);
    //sm.draw(VP_dummy);
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
        plane.speed_y += 0.001f;
    else if(w)
        plane.speed_x += 0.001f;
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
        plane.position.y += 0.1f;
        plane.part1.position.y += 0.1f;
        plane.part2.position.y += 0.1f; 
        plane.part3.position.y += 0.1f;
        plane.part4.position.y += 0.1f;       
    }
    if(down)
    {
        plane.position.y -= 0.1f;
        plane.part1.position.y -= 0.1f;
        plane.part2.position.y -= 0.1f;
        plane.part3.position.y -= 0.1f;
        plane.part4.position.y -= 0.1f;  
    }
    if(forward)
    {
        pressl++;
        if (pressl == 4)
        {
        glm::vec3 v = plane.part2.position - plane.part1.position;
         v=  glm::normalize(v);
        cout<<plane.part1.position.x<<" "<<plane.part1.position.y<<" "<<plane.part1.position.z<<" pos part1 \n";
        cout<<plane.position.x<<" "<<plane.position.y<<" "<<plane.position.z<<" pos \n";
        plane.position += v;
        cout<<plane.position.x<<" "<<plane.position.y<<" "<<plane.position.z<<" pos after \n";
        plane.part1.position += v;
        plane.part2.position += v;
        plane.part3.position += v;    
        plane.part4.position += v;
        pressl = 0;
        }

    }
    if(create)
    {
        pressr++;
        if(pressr == 5)
        {
        background.create();
        pressr = 0;
        }
    }

    
    /*else if(left)
    {
        pressl++;
        if (pressl == 6)
        {
        cout<<"left clicked\n";
        plane.shoot(1);
        pressl = 0;
        }
    }
    else if(right)
    {
        cout<<"rightt clicked\n";
        pressr++;
        if (pressr == 6)
        {
        cout<<"right clicked\n";
        plane.shoot(2);
        pressr = 0;
        }      
    }*/


    /*if (f){ // first person 
        t=0;
        theta =0;
        phi = 0;
    }

    //all remaining are at an angle above the 2 sqaures 
    if (left) {
        t=1;
        phi += 0.05;
    }
    else if(right){
        //cout<<"right";
        t=1;
        phi -= 0.05;
    }
    else if(up){
        t=1;
        theta += 0.05;
    }
    else if(down){
        t=1;
        theta -= 0.05;
    }*/
}

void tick_elements() {
    ring.tick();
    plane.tick();
    float t = (-1)*((plane.position.y/10)*90.0f);
    if (t > -90.0f && t < 90.0f)
        dashboard.rotation = t;
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

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    ball1       = Ball(-0.5f, 0,0,0.5f, COLOR_RED);
    ball2       = Ball(0, 0, 10,0.5f,COLOR_GREEN);
    plane = Plane(0,0,0);
    background = Background(1);
    dashboard = Dashboard(1);
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
