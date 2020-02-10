#pragma once

#include "Core.h"
#include "Renderer.h"

#include "Components/Transform.h"
#include "Components/Mesh.h"

#include <Entt/entt.hpp>

namespace Ohm {
	class CScene final {
	public:
		CScene() = default;
		CScene(const CScene&) = delete;
		CScene(CScene&&) = delete;

		virtual ~CScene() = default;

	public:
		auto& operator =(const CScene&) = delete;

	public:
		void Update(double deltaTime) {

		}
		void Render(double deltaTime) {
			ENGINE_MEASURE_BEGIN(SceneTraversal);
			mRegistry.view<CTransform, CMesh>().each([&](
				auto& transform,
				auto& mesh) {
					mRenderer.Submit(transform, mesh);
				});
			ENGINE_MEASURE_END(SceneTraversal);

			ENGINE_MEASURE_BEGIN(LambertRenderPass);
			mRenderer.LambertRenderPass();
			ENGINE_MEASURE_END(LambertRenderPass);
		}

	public:
		inline auto CreateEntity() { return mRegistry.create(); }

		template<typename Component, typename ... Args>
		void AddComponent(const entt::entity& entity, Args&& ... args) {
			mRegistry.assign<Component>(entity, std::forward<Args>(args) ...);
		}

		template<typename ... Components>
		auto GetComponents(const entt::entity& entity) {
			return mRegistry.get<Components>(entity);
		}

	private:
		entt::registry mRegistry;

		CRenderer mRenderer;
	};
}