#pragma once

namespace Light {

	class Shader
	{
	private:
	public:
		static Shader* Create(const std::string& vertexPath, const std::string& pixelPath);

		virtual ~Shader() = default;

		virtual void Bind() = 0;
		virtual void UnBind() = 0;

	protected:
		Shader() = default;
	};

}