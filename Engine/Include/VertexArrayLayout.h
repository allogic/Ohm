#pragma once

#include "Core.h"

namespace Ohm {
	struct SVertexArrayLayoutAttribute {
		int index;
		int stride;

		std::vector<float> data;
	};

	using TVboLayout = std::vector<SVertexArrayLayoutAttribute>;
	using TEboLayout = std::vector<unsigned int>;

	class CVertexArrayLayout {
	public:
		CVertexArrayLayout(const TVboLayout& attributes, const TEboLayout& indices);

		virtual ~CVertexArrayLayout();

	public:
		void Bind() const;
		void Draw() const;

	private:
		unsigned int mAttribSize = 0;
		unsigned int mIndicesSize = 0;

		unsigned int mVao = 0;
		unsigned int mEbo = 0;

		std::vector<unsigned int> mVbos;
	};
}