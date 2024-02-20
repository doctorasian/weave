#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 fragPos;
out vec3 triColor;

uniform float horizontalOffset;

void main() {
	//gl_Position = vec4(aPos.x + horizontalOffset, -aPos.y * horizontalOffset, aPos.z + horizontalOffset, 1.0);
	fragPos = aPos;
	gl_Position = vec4(aPos, 1.0f);
	triColor = aColor;
}
