#version 450 core

layout (location = 0) in vec3 aPos;

int main
{
	gl_Position = vec4(aPos, 1.f);
}
