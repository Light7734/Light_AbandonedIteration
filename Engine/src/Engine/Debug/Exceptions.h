#pragma once

#define DXC(x) if(FAILED(hr = x)) throw dxException(hr, __FILE__, __LINE__)

namespace Light {
	
	struct FailedAssertion : std::exception
	{
		FailedAssertion(const char* file, int line);
	};

	// OpenGL
	struct glException : std::exception
	{
		glException(unsigned int source, unsigned int type, unsigned int id, const char* msg);
	};

#ifdef LIGHT_PLATFORM_WINDOWS
	// DirectX
	struct dxException : std::exception
	{
		dxException(long hr, const char* file, int line);
	};
#endif

}