#pragma once

#include "Core.h"

namespace Ohm {
	class CShader final {
	public:
		CShader();
		CShader(const CShader&) = delete;
		CShader(CShader&&) = delete;

		virtual ~CShader();

	public:
		auto& operator =(const CShader&) = delete;

	public:
		bool Compile(const std::string& vertexSource, const std::string& fragmentSource);
		void Bind() const;

	private:
		bool CompileShader(unsigned int& shader, const std::string& source);
		bool LinkShaders();
		bool CheckStatus(unsigned int shader, unsigned int type, std::string& log) const;

	private:
		unsigned int mVso;
		unsigned int mFso;

		unsigned int mProgram;
	};
}