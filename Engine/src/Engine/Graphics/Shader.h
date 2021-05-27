#pragma once

namespace Light {

	class Shader
	{
	private:
	public:
		static Shader* Create();

		virtual ~Shader() = default;

		virtual void Bind() = 0;
		virtual void UnBind() = 0;

	protected:
		Shader() = default;
	};

}