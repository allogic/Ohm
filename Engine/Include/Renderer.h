#pragma once

#include "Core.h"
#include "Job.h"
#include "Shader.h"

namespace Ohm {
	using namespace ::Ohm::Components;

	class CRenderer final {
	public:
		CRenderer() = default;
		CRenderer(const CRenderer&) = delete;
		CRenderer(CRenderer&&) = delete;

	public:
		auto& operator =(const CRenderer&) = delete;

	public:
		inline void Submit(CTransform& transform, CMesh& mesh) {
			mLambertRenderPassQueue.emplace_back(&transform, &mesh);
		}

		void LambertRenderPass() {
			//std::sort(mLambertRenderPassQueue.begin(), mLambertRenderPassQueue.end());

			while (!mLambertRenderPassQueue.empty()) {
				const auto& job = mLambertRenderPassQueue.back();

				mLambertRenderPassQueue.pop_back();
			}
		};

	private:
		std::vector<SJob> mLambertRenderPassQueue;
	};
}