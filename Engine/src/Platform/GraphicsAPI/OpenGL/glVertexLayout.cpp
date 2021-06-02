#include "ltpch.h"
#include "glVertexLayout.h"

#include "glBuffers.h"

#include <glad/glad.h>

namespace Light {

	glVertexLayout::glVertexLayout(VertexBuffer* buffer, const std::vector<std::pair<std::string, VertexElementType>>& elements)
	{
		// sanity check
		LT_ENGINE_ASSERT(dynamic_cast<glVertexBuffer*>(buffer), "glVertexLayout::glVertexLayout: failed to cast VertexBuffer to glVertexBuffer");

		// elements desc
		std::vector<glVertexElementDesc> elementsDesc;

		unsigned int stride = 0u;
		for(const auto& element : elements)
		{
			elementsDesc.push_back(GetElementDesc(element.second, stride));
			stride += elementsDesc.back().typeSize * elementsDesc.back().count;
		}

		// bind
		glCreateVertexArrays(1, &m_ArrayID);
		buffer->Bind();
		Bind();

		// vertex attributes
		unsigned int index = 0u;
		for (const auto& elementDesc : elementsDesc)
		{
			glVertexAttribPointer(index, elementDesc.count, elementDesc.type, GL_FALSE, stride, (const void*)elementDesc.offset);
			glEnableVertexAttribArray(index++);
		}
	}

	glVertexLayout::~glVertexLayout()
	{
		glDeleteVertexArrays(1, &m_ArrayID);
	}

	void glVertexLayout::Bind()
	{
		glBindVertexArray(m_ArrayID);
	}

	void glVertexLayout::UnBind()
	{
		glBindVertexArray(NULL);
	}

	glVertexElementDesc glVertexLayout::GetElementDesc(VertexElementType type, unsigned int offset)
	{
		switch (type)
		{
		case VertexElementType::Int1: return { GL_INT, 1, sizeof(int), offset };
		case VertexElementType::Int2: return { GL_INT, 2, sizeof(int), offset };
		case VertexElementType::Int3: return { GL_INT, 3, sizeof(int), offset };
		case VertexElementType::Int4: return { GL_INT, 4, sizeof(int), offset };

		case VertexElementType::UInt1: return { GL_UNSIGNED_INT, 1, sizeof(unsigned int), offset };
		case VertexElementType::UInt2: return { GL_UNSIGNED_INT, 2, sizeof(unsigned int), offset };
		case VertexElementType::UInt3: return { GL_UNSIGNED_INT, 3, sizeof(unsigned int), offset };
		case VertexElementType::UInt4: return { GL_UNSIGNED_INT, 4, sizeof(unsigned int), offset };

		case VertexElementType::Float1: return { GL_FLOAT, 1, sizeof(float), offset };
		case VertexElementType::Float2: return { GL_FLOAT, 2, sizeof(float), offset };
		case VertexElementType::Float3: return { GL_FLOAT, 3, sizeof(float), offset };
		case VertexElementType::Float4: return { GL_FLOAT, 4, sizeof(float), offset };

		case VertexElementType::Double1: return { GL_DOUBLE, 1, sizeof(float), offset };
		case VertexElementType::Double2: return { GL_DOUBLE, 2, sizeof(float), offset };
		case VertexElementType::Double3: return { GL_DOUBLE, 3, sizeof(float), offset };
		case VertexElementType::Double4: return { GL_DOUBLE, 4, sizeof(float), offset };
		default:
			LT_ENGINE_ASSERT(false, "glVertexLayout::GetElementDesc: invalid vertex element type");
			return {};
		}
	}

}