#version 420

out vec4 outColor;

in vec3 vFragPos;
in vec3 vNorm;
in vec3 vTexCoord;

uniform vec3 lightPos = vec3(1, 5, -4);
uniform vec3 lightColor = vec3(.67, .6, .7) * 3;

uniform sampler2D tex1;

void main() {
	
	vec4 texColor = texture(tex1, vec2(vTexCoord));
	
	vec3 ambient = lightColor * .1;
	vec3 objectColor = ambient * vec3(.2, .6, .8);
	
	vec3 norm = normalize(vNorm);
	vec3 lightDir = normalize(lightPos - vFragPos);  
	
	float diffFactor = max(dot(lightDir, norm), 0);
	vec3 diffuse = diffFactor * lightColor;
	
	outColor = vec4((ambient + objectColor) * diffuse, 1.f) * texColor;
	
}