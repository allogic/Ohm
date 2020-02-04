#include <Ohm.h>

#define SANDBOX_DEMO_STRESS_LVL_SIMPLE 1000
#define SANDBOX_DEMO_STRESS_LVL_NORMAL 10000
#define SANDBOX_DEMO_STRESS_LVL_INSANE 100000

class CSandbox final : public Ohm::CApplication {
public:
	CSandbox() : CApplication({ 60, 1280, 720, "Demo" }) {
		for (unsigned int i = 0; i < SANDBOX_DEMO_STRESS_LVL_NORMAL; i++) {
			auto entity = mScene.CreateEntity();

			mScene.AddComponent<Ohm::CTransform>(entity);
			mScene.AddComponent<Ohm::CMesh>(entity);
		}
	}

	virtual ~CSandbox() override {

	}

public:
	void OnImGui(double deltaTime) override {
		ImGui::Text("some foo");
	}

	void OnUpdate(double deltaTime) override {

	}

	void OnRender(double deltaTime) const override {

	}
};

CREATE(CSandbox)