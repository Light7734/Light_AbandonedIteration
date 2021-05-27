#include "ltpch.h"
#include "glShader.h"

#include <GLAD/glad.h>

namespace Light {

	glShader::glShader(const std::string& vertexPath, const std::string& pixelPath)
	{
		m_ShaderID = glCreateProgram();

		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		unsigned int pixelShader = glCreateShader(GL_FRAGMENT_SHADER);

		const char* vertexPath_cstr = vertexPath.c_str();
		const char* pixelPath_cstr = pixelPath.c_str();

		glShaderSource(vertexShader, 1, &vertexPath_cstr, NULL);
		glShaderSource(pixelShader, 1, &pixelPath_cstr, NULL);

		glCompileShader(vertexShader);
		glCompileShader(pixelShader);

		// TEMP
		int isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<char> errorLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &errorLog[0]);

			glDeleteShader(vertexShader);
		}

		glGetShaderiv(pixelShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(pixelShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<char> errorLog(maxLength);
			glGetShaderInfoLog(pixelShader, maxLength, &maxLength, &errorLog[0]);

			glDeleteShader(pixelShader);
		}
		// TEMP

		glAttachShader(m_ShaderID, vertexShader);
		glAttachShader(m_ShaderID, pixelShader);
		glLinkProgram(m_ShaderID);
	
		glDeleteShader(vertexShader);
		glDeleteShader(pixelShader);

		// TODO: validate program
	}

	glShader::~glShader()
	{
		glDeleteProgram(m_ShaderID);
	}

	void glShader::Bind()
	{
		glUseProgram(m_ShaderID);
	}

	void glShader::UnBind()
	{
		glUseProgram(NULL);
	}

}