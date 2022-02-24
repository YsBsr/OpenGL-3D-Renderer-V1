#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>
#include <vector>

#include <glew.h>
#include <glfw3.h>

#include "stb_image/stb_image.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "OBJFileReader.h"
#include "Shader.h";
#include "Texture.h";
#include "VertexArrayObject.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Object3D.h"

int main() {

	GLFWwindow* window;

	if (!glfwInit())
		return -1;

	window = glfwCreateWindow(1280, 720, "3D Renderer from Scratch with OpenGL", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	unsigned int err = glewInit();

	if (GLEW_OK != err)
		std::cout << "Glew not loaded" << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;

	int b;
	glGetIntegerv(GL_GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX, &b);
	std::cout << "\n********\n" << b << "\n********\n" << std::endl;

	int a1;
	glGetIntegerv(GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &a1);

	std::cout << "\n********\n" << a1 << "\n********\n" << std::endl;

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_STENCIL_TEST);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	/*Uncomment to see changes*/
	Shader shader1("Resource/Shader/Light_Shader.shader");
	//Shader shader1("Resource/Shader/Texture_Shader.shader");
	

	shader1.Bind();

	std::vector<OBJpolygon> cube1;

	OBJFileReader shape1("Resource/obj/maymun.obj");
	cube1 = shape1.getPolygonBuffer();

	Texture tex1("Resource/Texture/texture1.jpg");
	tex1.getUnifrom1iLocation("tex", shader1.program);
	tex1.Bind(0);

	/*Texture tex2("Resource/Texture/texture.jpg");
	tex2.getUnifrom1iLocation("tex", shader1.program);
	tex2.Bind(1);*/

	Object3D obj1(cube1, shader1.program, &tex1);
	obj1.bindVertexArrayObjectToMesh();

	VertexArrayObject* mesh1;
	mesh1 = obj1.obj_mesh;

	glm::mat4 view = glm::lookAt(
		glm::vec3(6.0f, 6.0f, 6.6f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 1.0f)
	);

	glm::mat4 trans = glm::mat4(1.0f);
	int uniTrans = glGetUniformLocation(shader1.program, "trans"); 
	glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans)); 

	int uniView = glGetUniformLocation(shader1.program, "view");
	glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));

	glm::mat4 proj = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);
	int uniProj = glGetUniformLocation(shader1.program, "proj");
	glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));

	int light = glGetUniformLocation(shader1.program, "lightingColor");
	glUniform4f(light, 1.0f, 1.0f, 1.0f, 1.0f);

	int objColor = glGetUniformLocation(shader1.program, "objectColor");
	glUniform4f(objColor, 1.0f, 0.5f, 0.8f, 1.0f);

	int lightPos = glGetUniformLocation(shader1.program, "lightPosition");
	glUniform4f(lightPos, 1.0f, 1.0f, 0.0f, 1.0f);

	int viewPos = glGetUniformLocation(shader1.program, "viewerPosition");
	glUniform4f(viewPos, 2.0f, 2.0f, 2.2f, 0.0f);

	int constant = glGetUniformLocation(shader1.program, "constant");
	glUniform1f(constant, 1.0f);

	int linear = glGetUniformLocation(shader1.program, "linear_");
	glUniform1f(linear, 0.01f);

	int quadratic = glGetUniformLocation(shader1.program, "quadratic");
	glUniform1f(quadratic, 0.001f);

	auto t_start = std::chrono::high_resolution_clock::now();

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);
		glClear(GL_STENCIL_BUFFER_BIT);

		auto t_now = std::chrono::high_resolution_clock::now();
		float time = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();

		for (int i = 0; i < obj1.obj_mesh_length; i++)
		{
			mesh1[i].Bind();

			trans = glm::translate(glm::mat4(1.0f), glm::vec3(3.0f, -3.0f, 0.0f));
			trans = glm::rotate(trans, time * glm::radians(15.0f), glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

			trans = glm::translate(glm::mat4(1.0f), glm::vec3(-3.0f, -3.0f, 0.0f));
			trans = glm::rotate(trans, time * glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

			trans = glm::translate(glm::mat4(1.0f), glm::vec3(-3.0f, 3.0f, 0.0f));
			trans = glm::rotate(trans, time * glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
			glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			
		}
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	int a2;
	glGetIntegerv(GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &a2);

	std::cout << "\n********\n" << a2 << "\n********\n" << std::endl;

	glfwTerminate();

	return 0;
}
