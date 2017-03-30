#pragma once

#include <string>
#include <GL/glew.h>
#include <glm/fwd.hpp>

namespace clone { namespace graphics {

	class Shader
	{
	private:
		GLuint m_programId;
		std::string m_vertPath;
		std::string m_fragPath;
	public:
		Shader(const std::string& vertPath, const std::string& fragPath);
		~Shader();

		void setUniform1f(const GLchar* name, float value);
		void setUniform1i(const GLchar* name, int value);
		void setUniform2f(const GLchar* name, const glm::vec2& value);
		void setUniform3f(const GLchar* name, const glm::vec3& value);
		void setUniform4f(const GLchar* name, const glm::vec4& value);

		void setUniformMat4(const GLchar* name, const glm::mat4& value);

		void enable() const;
		void disable() const;
	private:
		GLuint load() const;
		bool checkShaderError(GLuint shader, GLuint flag, const std::string& errorMsg) const;
		bool checkShaderProgramError(GLuint program, GLuint flag,
			const std::string& errorMsg) const;
		GLint getUniformLocation(const GLchar* name);
	};

}
}