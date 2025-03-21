#define STB_IMAGE_IMPLEMENTATION

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <shader/shader.h>

#include <iostream>
#include <math.h>

#include "stb_image/stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// forward declarations
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
   // glfw: initialize and configure
   glfwInit();
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

   // glfw window creation
   GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr,nullptr);
   if(window == nullptr)
   {
      std::cout << "Failed to create GLFW window" << std::endl;
      glfwTerminate();
      return -1;
   }
   glfwMakeContextCurrent(window);
   glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

   // glad: load all OpenGL function pointers
   if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
   {
      std::cout << "Failed to initialize GLAD" << std::endl;
      return -1;
   }

   // configure global opengl state
   // -------------------------------------------
   glEnable(GL_DEPTH_TEST);


   // build and compile our shader program
   // ---------------------------------------
   Shader ourShader("../shaders/learnopengl/4.6.shader.vs", "../shaders/learnopengl/4.6.shader.fs");
   
   // set up vertex data (and buffer(s)) and configure vertex attributes
   //-----------------------------------------------------------------
   float vertices[]{
      // positions       // colors
      0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,// bottom right
     -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,// bottom left
      0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,// top
   };

   unsigned int VBO, VAO;
   glGenVertexArrays(1, &VAO);
   glGenBuffers(1, &VBO);
   // bind the Vertes Arrays Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
   glBindVertexArray(VAO);

   glBindBuffer(GL_ARRAY_BUFFER, VBO);
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

   // position attribute
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
   glEnableVertexAttribArray(0);

   // color atribute
   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
   glEnableVertexAttribArray(1);

    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

   // render loop
   //----------------------------------------
   while(!glfwWindowShouldClose(window))
   {
      // input
      processInput(window);
      
      // render
      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      ourShader.use();

      // draws the triangle
      glBindVertexArray(VAO); //not necessary here because we only have a single VAO but doing it anyway to keep things more organized
      glDrawArrays(GL_TRIANGLES, 0, 3);
      //glBindVertexArray(0); //no need to unbind it every time

      // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
      //------------------------------------------
      glfwSwapBuffers(window);
      glfwPollEvents();
   }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

   // glfw: terminate, clearing all previously allocated GLFW resources
   //---------------------------------------------------
   glfwTerminate();

   return 0;
}

// called every loop to check whether ESC is pressed. If that's the case the window closes
void processInput(GLFWwindow *window)
{
   if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(window,true);
}

// checks whether the window has changed size to adjust the viewport too
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
   glViewport(0,0, width, height);
}
