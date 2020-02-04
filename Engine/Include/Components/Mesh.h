#pragma once

#include "../Shader.h"
#include "../VertexArrayLayout.h"

namespace Ohm::Components {
	class CMesh final {
	public:
		CMesh() = default;
		CMesh(CShader* pShader, CVertexArrayLayout* pVertexArrayLayout) :
			mpShader(pShader),
			mpVertexArrayLayout(pVertexArrayLayout) {}

	private:
		CShader* mpShader = nullptr;
		CVertexArrayLayout* mpVertexArrayLayout = nullptr;
	};
}