#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"


unsigned int VBO;
unsigned int vertexShader;
unsigned int fragmentShader;
unsigned int shaderProgram;
unsigned int VAO;
unsigned int EBO;

void initializeGLAD()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initalize GLAD" << std::endl;
	}

	std::cout << "GLAD INITIALIZED..." << std::endl;
}

void framebufferCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0,0,width, height);

}


bool closeButton(GLFWwindow* window)
{
	if(glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
	{
		return false;
	}
	return true;

}


float vData[] =
{	//x   y      z		  //colors
	0.5f, 0.5f, 0.0f,	  1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.0f,	  0.0f, 1.0f, 0.0f,
	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,
	-0.5f, 0.5f, 0.0f,	  0.5f, 0.0f, 0.0f,
	-0.75f, 0.75f, 0.0f,  0.0f, 0.5f, 0.0f,
	0.25f, -0.25f, 0.0f,  0.0f, 0.0f, 0.5f,
	-0.25f, -0.75f, 0.0f, 0.5f, 0.5f, 0.5f
};

unsigned int indices[] =
{
	0,1,3, // first triangle
	1,2,3, // second triangle
	2,4,5, // third triangle
	3,5,6 // fourth triangle

};



int main()
{
	
	int height = 1280;
	int width = 720;
	bool open = true;
	bool wireMode = false;

	
	//initialize GLFW 
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	
	std::cout << "WINDOW INITIALIZED..." << std::endl;

	//creating window context
	GLFWwindow* window = glfwCreateWindow(height, width, "DYLANS AWESOME GAME!", NULL, NULL);

	if (window == NULL) 
	{
		std::cout << "Error instantiating window context" << std::endl;

		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferCallback);
	//									   ^^ idk how the fuck it takes in a function without parameters
	std::cout << "WINDOW CREATED..." << std::endl;
	initializeGLAD();


	Shader shader("vertexShader.vs", "fragmentShader.fs");

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);


	//generates vertex array object
	glBindVertexArray(VAO);


	//generates Vertex Buffer Object
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vData), vData, GL_STATIC_DRAW);


	//generating Element Buffer Object
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	//position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	//color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glBindVertexArray(0);



	while(open)
	{
		if(!glfwWindowShouldClose(window))
		{
			open = closeButton(window);


			// rendering commands go here // 
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			shader.use();


			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
			

			if(glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
			{
				wireMode = true;
				std::cout << "WIREMODE ACTIVATED" << std::endl;
			}else if(glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS)
			{
				wireMode = false;
				std::cout << "WIREMODE DE-ACTIVATED" << std::endl;
			}


			if(wireMode == true)
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}

			if(wireMode == false)
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}

			glfwSwapBuffers(window);
			glfwPollEvents();
			
		}
	
	}


	//cleaning everything up after game loop has closed
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);
	glfwTerminate();
	std::cout << "GAME SUCCESSFULLY CLOSED!" << std::endl;


	return 0;
}