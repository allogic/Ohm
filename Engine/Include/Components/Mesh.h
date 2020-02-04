#pragma once

#include "../VertexArrayLayout.h"

namespace Ohm {
	class CMesh final {
	public:
		CMesh() = default;
		CMesh(CVertexArrayLayout* pVertexArrayLayout) :
			mpVertexArrayLayout(pVertexArrayLayout) {}

	private:
		CVertexArrayLayout* mpVertexArrayLayout = nullptr;
	};
}