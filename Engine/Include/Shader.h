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
		void Bind() const;

	protected:
		bool Compile();

	private:
		bool CompileShader(unsigned int& shader, const std::string& source);
		bool LinkShaders();
		bool CheckStatus(unsigned int shader, unsigned int type, std::string& log) const;

	protected:
		std::string mVertexSource;
		std::string mFragmentSource;

	private:
		unsigned int mVso;
		unsigned int mFso;

		unsigned int mProgram;
	};
}