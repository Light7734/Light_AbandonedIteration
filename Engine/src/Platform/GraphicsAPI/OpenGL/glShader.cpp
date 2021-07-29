#include "ltpch.h"
#include "glShader.h"

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Light {

	glShader::glShader(const std::string& vertexSource, const std::string& fragmentSource)
		: m_ShaderID(NULL)
	{
		m_ShaderID = glCreateProgram();

		// create shaders
		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// &(address of) needs an lvalue
		const char* lVertexSource = vertexSource.c_str();
		const char* lFragmentSource = fragmentSource.c_str();

		// set shaders' source code
		glShaderSource(vertexShader, 1, &lVertexSource, NULL);
		glShaderSource(fragmentShader, 1, &lFragmentSource, NULL);

		// compile shaders
		glCompileShader(vertexShader);
		glCompileShader(fragmentShader);

		/* #TEMP_HANDLE_SHADER_COMPILE_FAILURE# */
		int isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			int logLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &logLength);

			char* errorLog = (char*)alloca(logLength);
			glGetShaderInfoLog(vertexShader, logLength, &logLength, &errorLog[0]);

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			LT_ENGINE_ASSERT(false, "glShader::glShader: failed to compile vertex shader:\n        {}", errorLog);

			return;
		}

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			int logLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &logLength);

			char* errorLog = (char*)alloca(logLength);
			glGetShaderInfoLog(fragmentShader, logLength, &logLength, &errorLog[0]);

			glDeleteShader(fragmentShader);
			glDeleteShader(vertexShader);

			LT_ENGINE_ASSERT(false, "glShader::glShader: failed to compile fragment shader:\n        {}", errorLog);

			return;
		}
		/* #TEMP_HANDLE_SHADER_COMPILE_FAILURE# */

		// attach shaders
		glAttachShader(m_ShaderID, vertexShader);
		glAttachShader(m_ShaderID, fragmentShader);

		// link shader program
		glLinkProgram(m_ShaderID);
	
		// delete shaders (free memory)
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
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