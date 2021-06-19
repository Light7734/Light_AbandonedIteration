#include "ltpch.h"
#include "glShader.h"

#include <glad/glad.h>

namespace Light {

	glShader::glShader(const std::string& vertexSource, const std::string& fragmentSource)
	{
		m_ShaderID = glCreateProgram();

		// create shaders
		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		unsigned int pixelShader = glCreateShader(GL_FRAGMENT_SHADER);

		// & (address of) needs an lvalue
		const char* lVertexSource = vertexSource.c_str();
		const char* lFragmentSource = fragmentSource.c_str();

		// set shaders' sorce code
		glShaderSource(vertexShader, 1, &lVertexSource, NULL);
		glShaderSource(pixelShader, 1, &lFragmentSource, NULL);

		// compile shaders
		glCompileShader(vertexShader);
		glCompileShader(pixelShader);

		//* TEMP__ HANDLE SHADER COMPILE FAILURE __TEMP **//
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
		//* TEMP__ HANDLE SHADER COMPILE FAILURE __TEMP **//

		// attach and link shaders to the shader program
		glAttachShader(m_ShaderID, vertexShader);
		glAttachShader(m_ShaderID, pixelShader);
		glLinkProgram(m_ShaderID);
	
		// delete shaders (free memory)
		glDeleteShader(vertexShader);
		glDeleteShader(pixelShader);

		// #todo: validate program
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