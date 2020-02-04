#pragma once

#include "Components/Transform.h"
#include "Components/Mesh.h"

namespace Ohm {
	struct SJob {
		CTransform* pTransform;
		CMesh* pMesh;
	};
}