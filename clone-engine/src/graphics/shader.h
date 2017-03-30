#pragma once

#include <GL/glew.h>
#include <string>

namespace clone { namespace graphics {

	class Shader
	{
	private:
		GLuint m_shaderId;
		std::string m_vertPath;
		std::string m_fragPath;
	public:
		Shader(const std::string& vertPath, const std::string& fragPath);
		~Shader();

		void enable() const;
		void disable() const;
	private:
		GLuint load() const;
		bool checkShaderError(GLuint shader, GLuint flag, const std::string& errorMsg) const;
		bool checkShaderProgramError(GLuint program, GLuint flag,
			const std::string& errorMsg) const;
	};

}
}