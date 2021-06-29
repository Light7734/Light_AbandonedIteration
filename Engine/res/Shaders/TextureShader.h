#define LT_ENGINE_RESOURCES_TEXTURE_SHADER_VS \
R"(
+GLSL
#version 440 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoords;

out vec2 texCoords;

void main()
{
	gl_Position = vec4(a_Position, 1.0);
	texCoords = a_TexCoords;
}
-GLSL
)"

#define LT_ENGINE_RESOURCES_TEXTURE_SHADER_PS \
R"(
+GLSL
#version 440 core

in vec2 texCoords;

uniform sampler2D u_Texture;

out vec4 FragmentColor;

void main()
{
	FragmentColor = texture(u_Texture, texCoords);
}
-GLSL
)"