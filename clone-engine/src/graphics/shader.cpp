#include "shader.h"
#include "../utils/fileutils.h"

namespace clone { namespace graphics {

	Shader::Shader(const std::string & vertPath, const std::string & fragPath):
		m_vertPath(vertPath), m_fragPath(fragPath)
	{
		m_shaderId = load();
	}

	Shader::~Shader()
	{
	}

	void Shader::enable() const
	{
		glUseProgram(m_shaderId);
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
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
			std::cerr << errorMsg << ": " << error << std::endl;
			return true;
		}

		return false;
	}

	bool Shader::checkShaderProgramError(GLuint program, GLuint flag,
		const std::string & errorMsg) const
	{
		GLint success = 0;
		glGetProgramiv(program, flag, &success);

		if (success == GL_FALSE)
		{
			//TODO: Replace number with constant
			GLchar error[1024] = { 0 };
			glGetProgramInfoLog(program, sizeof(error), NULL, error);
			std::cerr << errorMsg << ": " << error << std::endl;
			return true;
		}

		return false;
	}

}
}