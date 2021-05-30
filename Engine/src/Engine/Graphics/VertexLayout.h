#pragma once

#include "Base.h"

#include <vector>

namespace Light {

	class VertexBuffer;

	enum class VertexElementType
	{
		Int1, Int2, Int3, Int4,
		UInt1, UInt2, UInt3, UInt4,
		Float1, Float2, Float3, Float4,
		Double1, Double2, Double3, Double4
	};

	class VertexLayout
	{
	public:
		static VertexLayout* Create(VertexBuffer* buffer, const std::vector<VertexElementType>& elements);

		virtual ~VertexLayout() = default;;

		virtual void Bind() = 0;
		virtual void UnBind() = 0;

	protected:
		VertexLayout() = default;
	};

}