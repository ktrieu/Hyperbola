#version 420

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;

layout(binding = 0) uniform mat4 mvp;

out vec3 fragPos;
out vec3 fragNormal;

void main() {
	fragPos = pos;
	fragNormal = normal;
	gl_Position = mvp * vec4(pos.xyz, 0);
}