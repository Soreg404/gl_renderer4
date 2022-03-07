#version 420 core

layout(location=0) in vec3 pos;
layout(location=1) in vec3 norm;
layout(location=2) in vec3 uv;

uniform mat4 model = mat4(1.f), view = mat4(1.f), projection = mat4(1.f);
uniform mat3 normalModel = mat3(1.f);

out vec3 vFragPos;
out vec3 vNorm;
out vec3 vTexCoord;

void main() {
	vec4 modelPos = model * vec4(pos, 1);
	gl_Position = projection * view * modelPos;
	vFragPos = vec3(modelPos);
	vNorm = normalModel * norm;
	vTexCoord = uv;
}