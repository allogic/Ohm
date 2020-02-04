#pragma once

#include "Components/Transform.h"
#include "Components/Mesh.h"

namespace Ohm {
	using namespace ::Ohm::Components;

	struct SJob {
		SJob() = default;
		SJob(CTransform* pTransform, CMesh* pMesh) :
			mpTransform(pTransform),
			mpMesh(pMesh) {}

		CTransform* mpTransform = nullptr;
		CMesh* mpMesh = nullptr;
	};
}