		
/*
Author: Bantwal Vaibhav Mallya 
Class: ECE 6122 A
Last Modified Date: 9th December 2023

File Description:
This file is an application which uses OpenGL to display and move objects in 3D space 

*/

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
// Include GLEW
#include <GL/glew.h>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>

// Include GLFW
#include <glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/norm.hpp>
using namespace glm;
using namespace std;
// Include AntTweakBar
#include <AntTweakBar.h>


#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/controls.hpp>
#include <common/objloader.hpp>
#include <common/vboindexer.hpp>
#include <common/quaternion_utils.hpp> // See quaternion_utils.cpp for RotationBetweenVectors, LookAt and RotateTowards

//initial positions and orientations of the four suzanne heads 
vec3 gPosition1(-2.0f, 0.0f, 1.0f);
vec3 gOrientation1;
 
vec3 gPosition2( 2.0f, 0.0f, 1.0f);
quat gOrientation2;

vec3 gPosition3( 0.0f, 2.0f, 1.0f);
vec3 gOrientation3;
 
vec3 gPosition4( 0.0f,-2.0f, 1.0f);
quat gOrientation4;

//random numbers to facilitate random translation for the suzanne heads 
float translateX1 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
float translateY1 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
float translateZ1 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

float translateX2 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
float translateY2 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
float translateZ2 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

float translateX3 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
float translateY3 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
float translateZ3 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

float translateX4 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
float translateY4 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
float translateZ4 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
 

//boolean for moving objects when "g" key is pressed  
bool moveObject = false;

float speed = 10.0f;

float deltaTime; 




//Function to get "g" key as input so that the objects start their movement 
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_G && action == GLFW_PRESS) {
        moveObject = !moveObject;
    }
}


//checking collision

void checkCollision(){
  //checking the difference between x,y and z coordinates of objects 
  bool checkX12 = (abs(gPosition1.x - gPosition2.x) < 1.5f);
  bool checkX13 = (abs(gPosition1.x - gPosition3.x) < 1.5f);
  bool checkX14 = (abs(gPosition1.x - gPosition4.x) < 1.5f);
  bool checkX23 = (abs(gPosition2.x - gPosition3.x) < 1.5f);
  bool checkX24 = (abs(gPosition2.x - gPosition4.x) < 1.5f);
  bool checkX34 = (abs(gPosition3.x - gPosition4.x) < 1.5f);

  bool checkY12 = (abs(gPosition1.y - gPosition2.y) < 1.5f);
  bool checkY13 = (abs(gPosition1.y - gPosition3.y) < 1.5f);
  bool checkY14 = (abs(gPosition1.y - gPosition4.y) < 1.5f);
  bool checkY23 = (abs(gPosition2.y - gPosition3.y) < 1.5f);
  bool checkY24 = (abs(gPosition2.y - gPosition4.y) < 1.5f);
  bool checkY34 = (abs(gPosition3.y - gPosition4.y) < 1.5f);

  bool checkZ12 = (abs(gPosition1.z - gPosition2.z) < 1.5f);
  bool checkZ13 = (abs(gPosition1.z - gPosition3.z) < 1.5f);
  bool checkZ14 = (abs(gPosition1.z - gPosition4.z) < 1.5f);
  bool checkZ23 = (abs(gPosition2.z - gPosition3.z) < 1.5f);
  bool checkZ24 = (abs(gPosition2.z - gPosition4.z) < 1.5f);
  bool checkZ34 = (abs(gPosition3.z - gPosition4.z) < 1.5f);

  //if the difference between x, y and z coordinates of objects is less than 1.5, reverse the translation direction
  if(checkX12 && checkY12 && checkZ12){
	translateX1 *= -1;
  	gPosition1.x += translateX1 * deltaTime * speed;

	translateY1 *= -1;
  	gPosition1.y += translateY1 * deltaTime * speed;

	translateZ1 *= -1;
  	gPosition1.z += translateZ1 * deltaTime * speed;

        translateX2 *= -1;
  	gPosition2.x += translateX2 * deltaTime * speed;

	translateY2 *= -1;
  	gPosition2.y += translateY2 * deltaTime * speed;

	translateZ2 *= -1;
  	gPosition2.z += translateZ2 * deltaTime * speed;
  }

  if(checkX13 && checkY13 && checkZ13){
	translateX1 *= -1;
  	gPosition1.x += translateX1 * deltaTime * speed;

	translateY1 *= -1;
  	gPosition1.y += translateY1 * deltaTime * speed;

	translateZ1 *= -1;
  	gPosition1.z += translateZ1 * deltaTime * speed;

        translateX3 *= -1;
  	gPosition3.x += translateX3 * deltaTime * speed;

	translateY3 *= -1;
  	gPosition3.y += translateY3 * deltaTime * speed;

	translateZ3 *= -1;
  	gPosition3.z += translateZ3 * deltaTime * speed;
  }

  if(checkX14 && checkY14 && checkZ14){
	translateX1 *= -1;
  	gPosition1.x += translateX1 * deltaTime * speed;

	translateY1 *= -1;
  	gPosition1.y += translateY1 * deltaTime * speed;

	translateZ1 *= -1;
  	gPosition1.z += translateZ1 * deltaTime * speed;

        translateX4 *= -1;
  	gPosition4.x += translateX4 * deltaTime * speed;

	translateY4 *= -1;
  	gPosition4.y += translateY4 * deltaTime * speed;

	translateZ4 *= -1;
  	gPosition4.z += translateZ4 * deltaTime * speed;
  }

  if(checkX23 && checkY23 && checkZ23){
	translateX2 *= -1;
  	gPosition2.x += translateX2 * deltaTime * speed;

	translateY2 *= -1;
  	gPosition2.y += translateY2 * deltaTime * speed;

	translateZ2 *= -1;
  	gPosition2.z += translateZ2 * deltaTime * speed;

        translateX3 *= -1;
  	gPosition3.x += translateX3 * deltaTime * speed;

	translateY3 *= -1;
  	gPosition3.y += translateY3 * deltaTime * speed;

	translateZ3 *= -1;
  	gPosition3.z += translateZ3 * deltaTime * speed;
  }

  if(checkX24 && checkY24 && checkZ24){
	translateX2 *= -1;
  	gPosition2.x += translateX2 * deltaTime * speed;

	translateY2 *= -1;
  	gPosition2.y += translateY2 * deltaTime * speed;

	translateZ2 *= -1;
  	gPosition2.z += translateZ2 * deltaTime * speed;

        translateX4 *= -1;
  	gPosition4.x += translateX4 * deltaTime * speed;

	translateY4 *= -1;
  	gPosition4.y += translateY4 * deltaTime * speed;

	translateZ4 *= -1;
  	gPosition4.z += translateZ4 * deltaTime * speed;
  }

  if(checkX24 && checkY24 && checkZ24){
	translateX2 *= -1;
  	gPosition2.x += translateX2 * deltaTime * speed;

	translateY2 *= -1;
  	gPosition2.y += translateY2 * deltaTime * speed;

	translateZ2 *= -1;
  	gPosition2.z += translateZ2 * deltaTime * speed;

        translateX4 *= -1;
  	gPosition4.x += translateX4 * deltaTime * speed;

	translateY4 *= -1;
  	gPosition4.y += translateY4 * deltaTime * speed;

	translateZ4 *= -1;
  	gPosition4.z += translateZ4 * deltaTime * speed;
  }

  if(checkX34 && checkY34 && checkZ34){
	translateX3 *= -1;
  	gPosition3.x += translateX3 * deltaTime * speed;

	translateY3 *= -1;
  	gPosition3.y += translateY3 * deltaTime * speed;

	translateZ3 *= -1;
  	gPosition3.z += translateZ3 * deltaTime * speed;

        translateX4 *= -1;
  	gPosition4.x += translateX4 * deltaTime * speed;

	translateY4 *= -1;
  	gPosition4.y += translateY4 * deltaTime * speed;

	translateZ4 *= -1;
  	gPosition4.z += translateZ4 * deltaTime * speed;
  }
  
  
}


int main( void )
{
 	srand((unsigned)time(NULL));

	//randomly choosing which axis to rotate about. 0 - X, 1 - Y, 2 - Z 
	int rotate_obj1 = rand()%3;
	int rotate_obj2 = rand()%3;
	int rotate_obj3 = rand()%3;
	int rotate_obj4 = rand()%3;


	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

	// Open a window and create its OpenGL context
	int windowWidth = 1024, windowHeight = 768;
	window = glfwCreateWindow(windowWidth, windowHeight, "Tutorial 17 - Rotations", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window.\n" );
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	
	//keycallback function to read the "g" key and start random movement of the suzanne heads 
	glfwSetKeyCallback(window, keyCallback);

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    	// Hide the mouse and enable unlimited mouvement
    	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    	// Set the mouse at the center of the screen
    	glfwPollEvents();
    	glfwSetCursorPos(window, 1024/2, 768/2);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS); 

	// Cull triangles which normal is not towards the camera
	//glEnable(GL_CULL_FACE);

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders( "StandardShading.vertexshader", "StandardShading.fragmentshader" );

	// Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");
	GLuint ViewMatrixID = glGetUniformLocation(programID, "V");
	GLuint ModelMatrixID = glGetUniformLocation(programID, "M");

	// Get a handle for our buffers
	GLuint vertexPosition_modelspaceID = glGetAttribLocation(programID, "vertexPosition_modelspace");
	GLuint vertexUVID = glGetAttribLocation(programID, "vertexUV");
	GLuint vertexNormal_modelspaceID = glGetAttribLocation(programID, "vertexNormal_modelspace");
	
	// Load the texture
	GLuint Texture = loadDDS("uvmap.DDS");
	
	// Get a handle for our "myTextureSampler" uniform
	GLuint TextureID  = glGetUniformLocation(programID, "myTextureSampler");

	// Read our .obj file
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	bool res = loadOBJ("suzanne.obj", vertices, uvs, normals);

	std::vector<unsigned short> indices;
	std::vector<glm::vec3> indexed_vertices;
	std::vector<glm::vec2> indexed_uvs;
	std::vector<glm::vec3> indexed_normals;
	indexVBO(vertices, uvs, normals, indices, indexed_vertices, indexed_uvs, indexed_normals);

	// Load it into a VBO

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, indexed_vertices.size() * sizeof(glm::vec3), &indexed_vertices[0], GL_STATIC_DRAW);

	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, indexed_uvs.size() * sizeof(glm::vec2), &indexed_uvs[0], GL_STATIC_DRAW);

	GLuint normalbuffer;
	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, indexed_normals.size() * sizeof(glm::vec3), &indexed_normals[0], GL_STATIC_DRAW);

	// Generate a buffer for the indices as well
	GLuint elementbuffer;
	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0] , GL_STATIC_DRAW);

	// Get a handle for our "LightPosition" uniform
	glUseProgram(programID);
	GLuint LightID = glGetUniformLocation(programID, "LightPosition_worldspace");

	

	// For speed computation
	double lastTime = glfwGetTime();
	double lastFrameTime = lastTime;
	int nbFrames = 0;


	//vertices of the oversized floor
	static const GLfloat g_vertex_buffer_data[] = {  
	   -100.0f,  -100.0f,  0.0f,
	   -100.0f,   100.0f,  0.0f,
		100.0f,   100.0f,  0.0f,
		100.0f,  -100.0f,  0.0f,
	   -100.0f,  -100.0f,  0.0f,
		100.0f,   100.0f,  0.0f
	};

	//vertices of the beach image
	static const GLfloat img_vertex_buffer_data[] = {  
	   -200.0f,  -200.0f,  0.0f,
	   -200.0f,   200.0f,  0.0f,
		200.0f,   200.0f,  0.0f,
		200.0f,  -200.0f,  0.0f,
	   -200.0f,  -200.0f,  0.0f,
		200.0f,   200.0f,  0.0f
	};

	//uv coordinates for the floor and the beach image 
	
	static const GLfloat g_uv[] = {  
	   0.0f,  0.0f,  
	   0.0f,   1.0f,  
		1.0f,   1.0f,  
		1.0f,  0.0f,  
	   0.0f,  0.0f,  
		1.0f,  1.0f,
	};
	static const GLfloat img_uv[] = {  
	   0.0f,  0.0f,  
	   0.0f,   1.0f,  
		1.0f,   1.0f,  
		1.0f,  0.0f,  
	   0.0f,  0.0f,  
		1.0f,  1.0f,
	};
	
	//image for the oversized floor 
	GLuint Texture1 = loadDDS("uvmap.DDS");

	//image for scenery 
        GLuint Texture2 = loadBMP_custom("beach.bmp");

        GLuint RectangleVertexBuffer;
	GLuint RectangleUVBuffer;

	GLuint ImgVertexBuffer;
	GLuint ImgUVBuffer;
	
	//buffers for oversized floor 
	glGenBuffers(1, &RectangleVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, RectangleVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	glGenBuffers(1, &RectangleUVBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, RectangleUVBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv), g_uv, GL_STATIC_DRAW);
	
	//buffers for the beach image behind the suzanne heads 
	glGenBuffers(1, &ImgVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, ImgVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(img_vertex_buffer_data), img_vertex_buffer_data, GL_STATIC_DRAW);

	glGenBuffers(1, &ImgUVBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, ImgUVBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(img_uv), g_uv, GL_STATIC_DRAW);

	do{

		// Measure speed
		double currentTime = glfwGetTime();
		deltaTime = (float)(currentTime - lastFrameTime); 
		lastFrameTime = currentTime;
		nbFrames++;
		if ( currentTime - lastTime >= 1.0 ){ // If last prinf() was more than 1sec ago
			// printf and reset
			printf("%f ms/frame\n", 1000.0/double(nbFrames));
			nbFrames = 0;
			lastTime += 1.0;
		}

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(programID);
		
		computeMatricesFromInputs();
		glm::mat4 ProjectionMatrix = getProjectionMatrix();
		glm::mat4 ViewMatrix = getViewMatrix();
		
		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture);
		// Set our "myTextureSampler" sampler to user Texture Unit 0
		glUniform1i(TextureID, 0);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(vertexPosition_modelspaceID);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			vertexPosition_modelspaceID,  // The attribute we want to configure
			3,                            // size
			GL_FLOAT,                     // type
			GL_FALSE,                     // normalized?
			0,                            // stride
			(void*)0                      // array buffer offset
		);

		// 2nd attribute buffer : UVs
		glEnableVertexAttribArray(vertexUVID);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(
			vertexUVID,                   // The attribute we want to configure
			2,                            // size : U+V => 2
			GL_FLOAT,                     // type
			GL_FALSE,                     // normalized?
			0,                            // stride
			(void*)0                      // array buffer offset
		);

		// 3rd attribute buffer : normals
		glEnableVertexAttribArray(vertexNormal_modelspaceID);
		glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
		glVertexAttribPointer(
			vertexNormal_modelspaceID,    // The attribute we want to configure
			3,                            // size
			GL_FLOAT,                     // type
			GL_FALSE,                     // normalized?
			0,                            // stride
			(void*)0                      // array buffer offset
		);

		// Index buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

		//randomly changing light intensity
		glm::vec3 lightPos = glm::vec3(4,4,4);
		glUniform3f(LightID, lightPos.x * (float)rand()/RAND_MAX
				   , lightPos.y * (float)rand()/RAND_MAX
				   , lightPos.z * (float)rand()/RAND_MAX);

		

		{ 	
			//code for the first suzanne object
			
			//code for random rotation
			//int rotate_obj1 = rand()%3;
			if(rotate_obj1 == 0){
			  gOrientation1.x += 3.14159f/2.0f * deltaTime;
			}
			else if(rotate_obj1 == 1){
			  gOrientation1.y += 3.14159f/2.0f * deltaTime;
			}
		        else{
			  gOrientation1.z += 3.14159f/2.0f * deltaTime;
			}
			glm::mat4 RotationMatrix1 = eulerAngleYXZ(gOrientation1.y, gOrientation1.x, gOrientation1.z);
			glm::mat4 TranslationMatrix1 = translate(mat4(), gPosition1);
			glm::mat4 ScalingMatrix1 = scale(mat4(), vec3(1.0f, 1.0f, 1.0f));
			glm::mat4 rotation_matrix1 = glm::rotate(mat4(),glm::radians(90.0f),glm::vec3(1.0f,0.0f,0.0f));
			glm::mat4 second_rotation_matrix1 = glm::rotate(mat4(),glm::radians(270.0f),glm::vec3(0.0f,1.0f,0.0f));
			glm::mat4 ModelMatrix1;

			//code for random translation within the bounds of the window
			if(moveObject){
				
				gPosition1.x += translateX1 * deltaTime * speed;
				gPosition1.y += translateY1 * deltaTime * speed;
				gPosition1.z += translateZ1 * deltaTime * speed;
				
				//handle collision
				checkCollision();

				//reversing direction if it exceeds the bounds of the confined space 
				
				if(gPosition1.x <= -12.0f || gPosition1.x >= 12.0f){
					translateX1 *= -1;
					gPosition1.x += translateX1 * deltaTime * speed;
				}

				if(gPosition1.y <= -12.0f || gPosition1.y >= 12.0f){
					translateY1 *= -1;
					gPosition1.y += translateY1 * deltaTime * speed;
				}
				//-7 is the Z coordinate of the oversized floor 
				if(gPosition1.z <= -7.0f || gPosition1.z >= 12.0f){
					translateZ1 *= -1;
					gPosition1.z += translateZ1 * deltaTime * speed;
				}
				
				ModelMatrix1 = glm::translate(ModelMatrix1, glm::vec3(gPosition1.x,gPosition1.y,gPosition1.z));
				ModelMatrix1 = TranslationMatrix1 * RotationMatrix1 * ScalingMatrix1;
			}
			else{
				ModelMatrix1 = TranslationMatrix1 * ScalingMatrix1 * rotation_matrix1 * second_rotation_matrix1; 
			}

			glm::mat4 MVP1 = ProjectionMatrix * ViewMatrix * ModelMatrix1;
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP1[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix1[0][0]);
			glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
			glDrawElements(
				GL_TRIANGLES,      // mode
				indices.size(),    // count
				GL_UNSIGNED_SHORT,   // type
				(void*)0           // element array buffer offset
			);

		}
		{	
			//code for the second suzanne object

			//code for random rotation
			//int rotate_obj2 = rand()%3;
			if(rotate_obj2 == 0){
			  gOrientation2.x += 3.14159f/2.0f * deltaTime;
			}
			else if(rotate_obj2 == 1){
			  gOrientation2.y += 3.14159f/2.0f * deltaTime;
			}
		        else{
			  gOrientation2.z += 3.14159f/2.0f * deltaTime;
			}
			glm::mat4 RotationMatrix2 = eulerAngleYXZ(gOrientation2.y, gOrientation2.x, gOrientation2.z);
			glm::mat4 TranslationMatrix2 = translate(mat4(), gPosition2); 
			glm::mat4 ScalingMatrix2 = scale(mat4(), vec3(1.0f, 1.0f, 1.0f));
			glm::mat4 rotation_matrix2 = glm::rotate(mat4(),glm::radians(90.0f),glm::vec3(0.0f,0.0f,1.0f));
			glm::mat4 second_rotation_matrix2 = glm::rotate(mat4(),glm::radians(-270.0f),glm::vec3(1.0f,0.0f,0.0f));
			glm::mat4 ModelMatrix2;

			//code for random translation within the bounds of the window
			if(moveObject){
				gPosition2.x += translateX2 * deltaTime * speed;
				gPosition2.y += translateY2 * deltaTime * speed;
				gPosition2.z += translateZ2 * deltaTime * speed;

				//handle collision
				checkCollision();

				//reversing direction if it exceeds the bounds of the confined space 
				
				if(gPosition2.x <= -12.0f || gPosition2.x >= 12.0f){
					translateX2 *= -1;
					gPosition2.x += translateX2 * deltaTime * speed;
				}

				if(gPosition2.y <= -12.0f || gPosition2.y >= 12.0f){
					translateY2 *= -1;
					gPosition2.y += translateY2 * deltaTime * speed;
				}
				//-7 is the Z coordinate of the oversized floor 
				if(gPosition2.z <= -7.0f || gPosition2.z >= 12.0f){
					translateZ2 *= -1;
					gPosition2.z += translateZ2 * deltaTime * speed;
				}
				ModelMatrix2 = glm::translate(ModelMatrix2, glm::vec3(gPosition2.x,gPosition2.y,gPosition2.z));
				ModelMatrix2 = TranslationMatrix2 * RotationMatrix2 * ScalingMatrix2;
			}
			else{
				ModelMatrix2 = TranslationMatrix2 * ScalingMatrix2 * rotation_matrix2 * second_rotation_matrix2; 
			}

			glm::mat4 MVP2 = ProjectionMatrix * ViewMatrix * ModelMatrix2;
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP2[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix2[0][0]);
			glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);



			// Draw the triangles !
			glDrawElements(
				GL_TRIANGLES,      // mode
				indices.size(),    // count
				GL_UNSIGNED_SHORT,   // type
				(void*)0           // element array buffer offset
			);

		}
		{ 	
			//code for the third suzanne object

			//code for random rotation
			
			if(rotate_obj3 == 0){
			  gOrientation3.x += 3.14159f/2.0f * deltaTime;
			}
			else if(rotate_obj3 == 1){
			  gOrientation3.y += 3.14159f/2.0f * deltaTime;
			}
		        else{
			  gOrientation3.z += 3.14159f/2.0f * deltaTime;
			}
			
			glm::mat4 RotationMatrix3 = eulerAngleYXZ(gOrientation3.y, gOrientation3.x, gOrientation3.z);
			glm::mat4 TranslationMatrix3 = translate(mat4(), gPosition3); // A bit to the left
			glm::mat4 ScalingMatrix3 = scale(mat4(), vec3(1.0f, 1.0f, 1.0f));
			glm::mat4 rotation_matrix3 = glm::rotate(mat4(),glm::radians(180.0f),glm::vec3(0.0f,0.0f,1.0f));
			glm::mat4 second_rotation_matrix3 = glm::rotate(mat4(),glm::radians(-270.0f),glm::vec3(1.0f,0.0f,0.0f));
			glm::mat4 ModelMatrix3;

			//code for random translation 
			if(moveObject){
				gPosition3.x += translateX3 * deltaTime * speed;
				gPosition3.y += translateY3 * deltaTime * speed;
				gPosition3.z += translateZ3 * deltaTime * speed;

				checkCollision();

				//reversing direction if it exceeds the bounds of the confined space 
				
				if(gPosition3.x <= -12.0f || gPosition3.x >= 12.0f){
					translateX3 *= -1;
					gPosition3.x += translateX3 * deltaTime * speed;
				}

				if(gPosition3.y <= -12.0f || gPosition3.y >= 12.0f){
					translateY3 *= -1;
					gPosition3.y += translateY3 * deltaTime * speed;
				}
				//-7 is the Z coordinate of the oversized floor 
				if(gPosition3.z <= -7.0f || gPosition3.z >= 12.0f){
					translateZ3 *= -1;
					gPosition3.z += translateZ3 * deltaTime * speed;
				}
				ModelMatrix3 = glm::translate(ModelMatrix3, glm::vec3(gPosition3.x,gPosition3.y,gPosition3.z));
				ModelMatrix3 = TranslationMatrix3 * RotationMatrix3 * ScalingMatrix3;
			}
			else{
				ModelMatrix3 = TranslationMatrix3 * ScalingMatrix3 * rotation_matrix3 * second_rotation_matrix3;
			}

			glm::mat4 MVP3 = ProjectionMatrix * ViewMatrix * ModelMatrix3;
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP3[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix3[0][0]);
			glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);

			// Draw the triangles !
			glDrawElements(
				GL_TRIANGLES,      // mode
				indices.size(),    // count
				GL_UNSIGNED_SHORT,   // type
				(void*)0           // element array buffer offset
			);

		}
		{ 
			//code for fourth suzanne object

			//code for random rotation
			
			if(rotate_obj4 == 0){
			  gOrientation4.x += 3.14159f/2.0f * deltaTime;
			}
			else if(rotate_obj4 == 1){
			  gOrientation4.y += 3.14159f/2.0f * deltaTime;
			}
		        else{
			  gOrientation4.z += 3.14159f/2.0f * deltaTime;
			}
			
			glm::mat4 RotationMatrix4 = eulerAngleYXZ(gOrientation4.y, gOrientation4.x, gOrientation4.z);
			glm::mat4 TranslationMatrix4 = translate(mat4(), gPosition4); 
			glm::mat4 ScalingMatrix4 = scale(mat4(), vec3(1.0f, 1.0f, 1.0f));
			glm::mat4 second_rotation_matrix4 = glm::rotate(mat4(),glm::radians(90.0f),glm::vec3(1.0f,0.0f,0.0f));
			glm::mat4 ModelMatrix4;

			//code for random translation within the bounds of the window
			if(moveObject){
				gPosition4.x += translateX4 * deltaTime * speed;
				gPosition4.y += translateY4 * deltaTime * speed;
				gPosition4.z += translateZ4 * deltaTime * speed;

				checkCollision();

				//reversing direction if it exceeds the bounds of the confined space 
				
				if(gPosition4.x <= -12.0f || gPosition4.x >= 12.0f){
					translateX4 *= -1;
					gPosition4.x += translateX4 * deltaTime * speed;
				}

				if(gPosition4.y <= -12.0f || gPosition4.y >= 12.0f){
					translateY4 *= -1;
					gPosition4.y += translateY4 * deltaTime * speed;
				}
				//-7 is the Z coordinate of the oversized floor 
				if(gPosition4.z <= -7.0f || gPosition4.z >= 12.0f){
					translateZ4 *= -1;
					gPosition4.z += translateZ4 * deltaTime * speed;
				}
				ModelMatrix4 = glm::translate(ModelMatrix4, glm::vec3(gPosition4.x,gPosition4.y,gPosition4.z));
				ModelMatrix4 = TranslationMatrix4 * RotationMatrix4 * ScalingMatrix4;
			}
			else{
				ModelMatrix4 = TranslationMatrix4 * ScalingMatrix4 * second_rotation_matrix4;
			}

			glm::mat4 MVP4 = ProjectionMatrix * ViewMatrix * ModelMatrix4;
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP4[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix4[0][0]);
			glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);



			// Draw the triangles !
			glDrawElements(
				GL_TRIANGLES,      // mode
				indices.size(),    // count
				GL_UNSIGNED_SHORT,   // type
				(void*)0           // element array buffer offset
			);

		}

		//Code for displaying the oversized floor 
		glm::mat4 ModelMatrix_rect = glm::mat4(1.0);
		ModelMatrix_rect = glm::translate(ModelMatrix_rect, glm::vec3(0.0f, 0.0f, -7.0f));
		glm::mat4 MVP_rect = ProjectionMatrix * ViewMatrix * ModelMatrix_rect;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP_rect[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix_rect[0][0]);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, Texture1);
       		glUniform1i(TextureID, 1);
		glBindBuffer (GL_ARRAY_BUFFER, RectangleVertexBuffer);
		glVertexAttribPointer(vertexPosition_modelspaceID, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glBindBuffer(GL_ARRAY_BUFFER, RectangleUVBuffer);
		glVertexAttribPointer(
			vertexUVID,                   // The attribute we want to configure
			2,                            // size : U+V => 2
			GL_FLOAT,                     // type
			GL_FALSE,                     // normalized?
			0,                            //
			(void*)0                      // array buffer offset
			);
                glDrawArrays(GL_TRIANGLES, 0, 6);
                
		//code for displaying the image behind the suzanne heads (beach image)
		glm::mat4 ModelMatrix_img = glm::mat4(1.0);
		ModelMatrix_img = glm::translate(ModelMatrix_img, glm::vec3(0.0f, 0.0f, -7.0f));
		glm::mat4 rotation_matrix_img = glm::rotate(ModelMatrix_img,glm::radians(90.0f),glm::vec3(1.0f,0.0f,0.0f));
		glm::mat4 rotation_matrix_img2 = glm::rotate(rotation_matrix_img,glm::radians(-90.0f),glm::vec3(0.0f,1.0f,0.0f));
		glm::mat4 final_translation_matrix = glm::translate(rotation_matrix_img2,glm::vec3(0.0f,0.0f,50.0f));
		glm::mat4 MVP_img = ProjectionMatrix * ViewMatrix * final_translation_matrix;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP_img[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix_img[0][0]);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, Texture2);
       		glUniform1i(TextureID, 2);
		glBindBuffer (GL_ARRAY_BUFFER, ImgVertexBuffer);
		glVertexAttribPointer(vertexPosition_modelspaceID, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glBindBuffer(GL_ARRAY_BUFFER, ImgUVBuffer);
		glVertexAttribPointer(
			vertexUVID,                   // The attribute we want to configure
			2,                            // size : U+V => 2
			GL_FLOAT,                     // type
			GL_FALSE,                     // normalized?
			0,                            //
			(void*)0                      // array buffer offset
			);
                glDrawArrays(GL_TRIANGLES, 0, 6);
		
		glDisableVertexAttribArray(vertexPosition_modelspaceID);
		glDisableVertexAttribArray(vertexUVID);
		glDisableVertexAttribArray(vertexNormal_modelspaceID);


		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteBuffers(1, &normalbuffer);
	glDeleteBuffers(1, &elementbuffer);
	glDeleteProgram(programID);
	glDeleteTextures(1, &TextureID);

	// Close GUI and OpenGL window, and terminate GLFW
	//TwTerminate();
	glfwTerminate();

	return 0;
}

