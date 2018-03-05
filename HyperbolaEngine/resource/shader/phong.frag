#version 420

in vec3 fragPos;
in vec3 fragNormal;

out vec4 finalColor;

void main() {
	//let's not get too fancy yet
	finalColor = vec4(fragNormal.xyz, 1.0);
}