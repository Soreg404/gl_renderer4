#version 420 core

out vec4 color;

in vec3 vTexCoord;

uniform sampler2D tex1;

void main() {
	color = texture(tex1, vec2(vTexCoord));
}