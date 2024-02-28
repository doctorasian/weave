#version 330 core
in vec2 TexCoord;
out vec4 fragColor;

uniform sampler2D tileTexture;

void main() {
	fragColor = texture(tileTexture, TexCoord);
}
