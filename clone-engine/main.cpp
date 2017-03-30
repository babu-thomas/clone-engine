#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "src/graphics/shader.h"
#include "src/graphics/window.h"
#include <vector>

// To enable NVIDIA Graphics card
//extern "C" {
//	_declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
//}

int main()
{
	using namespace clone;
	using namespace graphics;

	Window window("Clone Engine!", 800, 600);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	Shader shader(".\\src\\shaders\\basic_shader.vert", ".\\src\\shaders\\basic_shader.frag");
	shader.enable();

	glm::mat4 ortho = glm::ortho(0.0f, 20.0f, 0.0f, 20.0f);
	shader.setUniformMat4("pr_matrix", ortho);
	shader.setUniformMat4("ml_matrix", glm::translate(glm::mat4(), glm::vec3(5, 5, 0)));
	
	GLfloat points[] = {
		0.0f,  0.0f, 0.0f,
		5.0f, 10.0f, 0.0f,
		10.0f, 0.0f, 0.0f
	};

	GLfloat colors[] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};

	// Generate Vertex Array object
	GLuint VAO;
	glGenVertexArrays(1, &VAO);

	// Generate Vertex Buffer objects for points and colors
	GLuint points_vbo, colors_vbo;
	glGenBuffers(1, &points_vbo);
	glGenBuffers(1, &colors_vbo);


	glBindVertexArray(VAO);
	// For points
	glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// For colors
	glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

	while (!window.closed())
	{
		window.clear();
		glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		window.update();
	}

	return 0;
}