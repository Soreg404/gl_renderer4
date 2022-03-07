#include "GLSR/include/glsr.h"

GLenum glShdType(glr::ShdType t) {
	switch(t) {
	case glr::ShdType::VERTEX: return GL_VERTEX_SHADER;
	case glr::ShdType::FRAGMENT: return GL_FRAGMENT_SHADER;
	}
	return GL_VERTEX_SHADER;
}
glr::shader::ShdComp::ShdComp(std::string src, ShdType type): source(src), type(type) {}
glr::shader::ShdComp::~ShdComp() { if(id) glDeleteShader(id); }

int glr::shader::ShdComp::compile() {
	if(id) return 1;
	else id = glCreateShader(glShdType(type));

	const char *src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	GLint success = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if(!success) {
		char infoLog[513] = {0};
		glGetShaderInfoLog(id, 512, NULL, infoLog);
		GLRLOG("%s", infoLog);
		glDeleteShader(id);
		id = 0;
	}
	return success;
}
int glr::shader::ShdComp::recompile() { if(id) glDeleteShader(id); id = 0; return compile(); }


void glr::Shader::attach(const glr::shader::ShdComp &shd) {
	if(!pid) pid = glCreateProgram();
	if(!shd.getId()) return;
	GLuint *sid = &sids.at(static_cast<int>(shd.getType()));
	if(*sid) glDetachShader(pid, *sid);
	*sid = shd.getId();
	glAttachShader(pid, *sid);
}



int glr::Shader::link() {
	if(!pid) { GLRLOG("attempted to link but nothing is attached"); return 0; }
	if(linked) { GLRLOG("attempted to link already linked program"); return 0; }
	glLinkProgram(pid);

	GLint success = 0;
	glGetProgramiv(pid, GL_LINK_STATUS, &success);
	if(!success) {
		char infoLog[513] = { 0 };
		glGetProgramInfoLog(pid, 512, NULL, infoLog);
		GLRLOG("%s", infoLog);
		clear();
	} else linked = true;
	for(GLuint &sid : sids) { if(sid) glDetachShader(pid, sid); sid = 0; }
	return success;
}
void glr::Shader::clear() {
	if(!pid) return;
	glDeleteProgram(pid);
	pid = 0;
	linked = false;
}

glr::Shader::~Shader() {}

void glr::Shader::use() const {
	if(!linked) { GLRLOG("attaempt to use unlinked program"); }
	else glUseProgram(pid);

	// bind textures
}

GLuint getULoc(GLuint id, const char *name) {
	glUseProgram(id);
	return glGetUniformLocation(id, name);
}
void glr::Shader::setFloat(const char *name, glm::vec1 v) const { glUniform1f(getULoc(pid, name), v.x); }
void glr::Shader::setFloat(const char *name, glm::vec2 v) const { glUniform2f(getULoc(pid, name), v.x, v.y); }
void glr::Shader::setFloat(const char *name, glm::vec3 v) const { glUniform3f(getULoc(pid, name), v.x, v.y, v.z); }
void glr::Shader::setFloat(const char *name, glm::vec4 v) const { glUniform4f(getULoc(pid, name), v.x, v.y, v.z, v.w); }
void glr::Shader::setMat(const char *name, glm::mat3 v) const { glUniformMatrix3fv(getULoc(pid, name), 1, GL_FALSE, glm::value_ptr(v)); }
void glr::Shader::setMat(const char *name, glm::mat4 v) const { glUniformMatrix4fv(getULoc(pid, name), 1, GL_FALSE, glm::value_ptr(v)); }

void glr::Shader::setCamera(const glr::Movable &mov, const glr::Camera &cam) const {
	setMat("view", mov.getView());
	setMat("projection", cam.getProj());
}

void glr::Shader::setModel(const glr::Movable &mov) const {
	glm::mat4 tr = mov.getTransform();
	setMat("model", tr);
	setMat("normalModel", mov.getNormalMatrix(tr));
}


