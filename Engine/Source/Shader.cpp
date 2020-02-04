#include "Shader.h"

#include <glad/glad.h>

Ohm::CShader::CShader() {
	mProgram = glCreateProgram();

	mVso = glCreateShader(GL_VERTEX_SHADER);
	mFso = glCreateShader(GL_FRAGMENT_SHADER);
}

Ohm::CShader::~CShader() {
	glDeleteShader(mVso);
	glDeleteShader(mFso);

	glDeleteProgram(mProgram);
}

void Ohm::CShader::Bind() const {
	glUseProgram(mProgram);
}

bool Ohm::CShader::Compile() {
	if (!CompileShader(mVso, mVertexSource)) return false;
	if (!CompileShader(mFso, mFragmentSource)) return false;

	return LinkShaders();
}

bool Ohm::CShader::CompileShader(unsigned int& shader, const std::string& source) {
	const char* pSource = source.c_str();

	glShaderSource(shader, 1, &pSource, nullptr);
	glCompileShader(shader);

	std::string log;

	if (CheckStatus(shader, GL_COMPILE_STATUS, log)) return true;

	ENGINE_TRACE(log);

	return false;
}

bool Ohm::CShader::LinkShaders() {
	glAttachShader(mProgram, mVso);
	glAttachShader(mProgram, mFso);

	glLinkProgram(mProgram);

	std::string log;

	if (CheckStatus(mProgram, GL_LINK_STATUS, log)) return true;

	ENGINE_TRACE(log);

	return false;
}

bool Ohm::CShader::CheckStatus(unsigned int shader, unsigned int type, std::string& log) const {
	int compileInfo, compileInfoSize;

	glGetShaderiv(shader, static_cast<GLenum>(type), &compileInfo);
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &compileInfoSize);

	if (compileInfoSize <= 0) return true;

	log.resize(compileInfoSize);

	glGetShaderInfoLog(shader, compileInfoSize, nullptr, &log[0]);

	return false;
}
