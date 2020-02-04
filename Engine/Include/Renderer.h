#pragma once

#include "Core.h"
#include "Job.h"

namespace Ohm {
	class CRenderer final {
	public:
		CRenderer() = default;
		CRenderer(const CRenderer&) = delete;
		CRenderer(CRenderer&&) = delete;

	public:
		auto& operator =(const CRenderer&) = delete;

	public:
		inline void Submit(CTransform& transform, CMesh& mesh) { mLambertRenderPassQueue.push_back({ &transform, &mesh }); }

		void LambertRenderPass() {
			//std::sort(std::execution::parallel_policy{}, mLambertRenderPassQueue.begin(), mLambertRenderPassQueue.end());

			while (!mLambertRenderPassQueue.empty()) {
				const auto& job = mLambertRenderPassQueue.back();

				mLambertRenderPassQueue.pop_back();
			}
		};

	private:
		std::vector<SJob> mLambertRenderPassQueue;
	};
}