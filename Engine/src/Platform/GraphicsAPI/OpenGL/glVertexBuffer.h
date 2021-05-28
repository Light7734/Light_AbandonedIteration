#pragma once

#include "Base.h"
#include "Graphics/VertexBuffer.h"

namespace Light {

	class glVertexBuffer : public VertexBuffer
	{
	private:
		unsigned int m_BufferID;
	public:
		glVertexBuffer(unsigned int count, float* vertices);
		~glVertexBuffer();

		void Bind() override;
		void UnBind() override;
	};

}