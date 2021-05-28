#include "ltpch.h"
#include "VertexBuffer.h"
#include "OpenGL/glVertexBuffer.h"

#include "GraphicsContext.h"

namespace Light {


	VertexBuffer* VertexBuffer::Create(unsigned int count, float* vertices)
	{
		switch (GraphicsContext::GetGraphicsAPI())
		{
		case GraphicsAPI::OpenGL:
			return new glVertexBuffer(count, vertices);
		}
	}

}