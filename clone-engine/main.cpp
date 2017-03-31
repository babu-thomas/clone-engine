#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "src/graphics/shader.h"
#include "src/graphics/window.h"
#include "src/graphics/buffers/buffer.h"
#include "src/graphics/buffers/indexbuffer.h"
#include "src/graphics/buffers/vertexarray.h"
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

	GLfloat vertices[] = {
		5.0f,  5.0f, 0.0f,
		5.0f, 15.0f, 0.0f,
		15.0f,  15.0f, 0.0f,
		15.0f,  5.0f, 0.0f
	};

	GLushort indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	GLfloat colors1[] = {
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f
	};

	GLfloat colors2[] = {
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	VertexArray sprite1, sprite2;
	IndexBuffer ibo(indices, 6);

	sprite1.addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
	sprite1.addBuffer(new Buffer(colors1,  4 * 3, 3), 1);

	sprite2.addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
	sprite2.addBuffer(new Buffer(colors2,  4 * 3, 3), 1);

	while (!window.closed())
	{
		window.clear();

		glm::mat4 trans;
		trans = glm::translate(trans, glm::vec3(5.0f, 5.0f, 0.0f));

		glm::mat4 trans2;
		trans2 = glm::translate(trans2, glm::vec3(-5.0f, -5.0f, 0.0f));

		glm::vec2 mouse = window.getMousePosition();
		float light_pos_x = mouse.x * 20 / 800;
		float light_pos_y = 20 - mouse.y * 20 / 600;
		shader.setUniform2f("light_pos", glm::vec2(light_pos_x, light_pos_y));

		sprite1.bind();
			ibo.bind();
			shader.setUniformMat4("ml_matrix", trans);
			glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);
		sprite1.unbind();

		sprite2.bind();
			ibo.bind();
			shader.setUniformMat4("ml_matrix", trans2);
			glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);
		sprite2.unbind();

		window.update();
	}

	return 0;
}