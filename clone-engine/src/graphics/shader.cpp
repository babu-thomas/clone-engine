#include "shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../utils/fileutils.h"

namespace clone { namespace graphics {

	Shader::Shader(const std::string& vertPath, const std::string& fragPath):
		m_vertPath(vertPath), m_fragPath(fragPath)
	{
		m_programId = load();
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_programId);
	}

	void Shader::setUniform1f(const GLchar *name, float value)
	{
		glUniform1f(getUniformLocation(name), value);
	}

	void Shader::setUniform1i(const GLchar *name, int value)
	{
		glUniform1i(getUniformLocation(name), value);
	}

	void Shader::setUniform2f(const GLchar *name, const glm::vec2& value)
	{
		glUniform2f(getUniformLocation(name), value.x, value.y);
	}

	void Shader::setUniform3f(const GLchar *name, const glm::vec3& value)
	{
		glUniform3f(getUniformLocation(name), value.x, value.y, value.z);
	}

	void Shader::setUniform4f(const GLchar * name, const glm::vec4 & value)
	{
		glUniform4f(getUniformLocation(name), value.x, value.y, value.z, value.w);
	}

	void Shader::setUniformMat4(const GLchar *name, const glm::mat4& value)
	{
		glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
	}

	void Shader::enable() const
	{
		glUseProgram(m_programId);
	}

	void Shader::disable() const
	{
		glUseProgram(0);
	}

	GLuint Shader::load() const
	{
		GLuint program = glCreateProgram();
		
		GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
		std::string vertSource = read_file(m_vertPath);
		if (vertSource.empty())
		{
			std::cerr << "Can't load vertex shader!" << std::endl;
			return 0;
		}
		const char *vertSourceChar = vertSource.c_str();
		glShaderSource(vertex, 1, &vertSourceChar, NULL);
		glCompileShader(vertex);
		if (checkShaderError(vertex, GL_COMPILE_STATUS, "Failed to compile vertex shader"))
		{
			glDeleteShader(vertex);
			return 0;
		}

		GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
		std::string fragSource = read_file(m_fragPath);
		if (fragSource.empty())
		{
			std::cerr << "Can't load fragment shader!" << std::endl;
			return 0;
		}
		const char* fragSourceChar = fragSource.c_str();
		glShaderSource(fragment, 1, &fragSourceChar, NULL);
		glCompileShader(fragment);
		if (checkShaderError(fragment, GL_COMPILE_STATUS, "Failed to compile fragment shader"))
		{
			glDeleteShader(fragment);
			return 0;
		}

		glAttachShader(program, vertex);
		glAttachShader(program, fragment);

		glLinkProgram(program);
		if (checkShaderProgramError(program, GL_LINK_STATUS, "Error: Program linking failed"))
		{
			return 0;
		}

		glValidateProgram(program);
		if (checkShaderProgramError(program, GL_VALIDATE_STATUS,
			"Error: Program validation failed"))
		{
			return 0;
		}

		// We don't need the actual shaders now
		glDeleteShader(vertex);
		glDeleteShader(fragment);

		return program;
	}

	bool Shader::checkShaderError(GLuint shader, GLuint flag, const std::string& errorMsg) const
	{
		GLint success = 0;
		glGetShaderiv(shader, flag, &success);

		if (success == GL_FALSE)
		{
			//TODO: Replace number with constant
			GLchar error[1024] = { 0 };
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
			std::cerr << errorMsg << ":\n" << error << std::endl;
			return true;
		}

		return false;
	}

	bool Shader::checkShaderProgramError(GLuint program, GLuint flag,
		const std::string& errorMsg) const
	{
		GLint success = 0;
		glGetProgramiv(program, flag, &success);

		if (success == GL_FALSE)
		{
			//TODO: Replace number with constant
			GLchar error[1024] = { 0 };
			glGetProgramInfoLog(program, sizeof(error), NULL, error);
			std::cerr << errorMsg << ":\n" << error << std::endl;
			return true;
		}

		return false;
	}

	GLint Shader::getUniformLocation(const GLchar *name)
	{
		//TODO: Cache the results as this is a slow operation
		return glGetUniformLocation(m_programId, name);
	}

}
}