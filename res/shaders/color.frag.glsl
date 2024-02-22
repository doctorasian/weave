#version 330 core
in vec3 triColor;
in vec3 fragPos;

out vec4 fragColor;

uniform float strobeLight;

void main() {
	fragColor = vec4(fragPos, 1.0f);
}
