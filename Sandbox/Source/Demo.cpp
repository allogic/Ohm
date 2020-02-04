#define ENGINE_GL_MAJOR 4
#define ENGINE_GL_MINOR 6

#include <Ohm.h>

#define SANDBOX_DEMO_STRESS_LVL_SIMPLE 1000
#define SANDBOX_DEMO_STRESS_LVL_NORMAL 10000
#define SANDBOX_DEMO_STRESS_LVL_INSANE 100000

const Ohm::TVboLayout attributes{
	{ 0, 3, {
			-1.f, -1.f,  0.f,
			-1.f,  1.f,  0.f,
			 1.f, -1.f,  0.f,
			 1.f,  1.f,  0.f,
		},
	},
	{ 0, 3, {
			 0.f,  0.f,  0.f,
			 0.f,  0.f,  0.f,
			 0.f,  0.f,  0.f,
			 0.f,  0.f,  0.f,
		},
	},
	{ 0, 2, {
			 0.f,  0.f,
			 0.f,  1.f,
			 1.f,  0.f,
			 1.f,  1.f,
		},
	}
};
const Ohm::TEboLayout indices{ 0, 2, 1, 2, 3, 1 };

class CSandbox final : public Ohm::CApplication {
public:
	CSandbox() : CApplication(60, 1280, 720, "Demo") {
		mpPhongShader = Ohm::Shader::CreatePhongShader();

		for (unsigned int i = 0; i < SANDBOX_DEMO_STRESS_LVL_NORMAL; i++) {
			auto entity = mScene.CreateEntity();

			mScene.AddComponent<Ohm::Components::CTransform>(entity);
			mScene.AddComponent<Ohm::Components::CMesh>(entity, mpPhongShader, mpVertexArrayLayout);
		}

		for (unsigned int i = 0; i < SANDBOX_DEMO_STRESS_LVL_NORMAL; i++) {
			auto entity = mScene.CreateEntity();

			mScene.AddComponent<Ohm::Components::CTransform>(entity);
			mScene.AddComponent<Ohm::Components::CMesh>(entity, mpPhongShader, mpVertexArrayLayout);
		}
	}

	virtual ~CSandbox() override {
		delete mpVertexArrayLayout;
		delete mpPhongShader;
	}

public:
	void OnImGui(double deltaTime) override {
		ImGui::Text(glm::to_string(WindowSize()).c_str());
		ImGui::Text(glm::to_string(MousePosition()).c_str());
	}

	void OnUpdate(double deltaTime) override {

	}

	void OnRender(double deltaTime) const override {

	}

	void OnEvent(const Ohm::SEvent& event) override {

	}

private:
	Ohm::CShader* mpPhongShader = nullptr;
	Ohm::CVertexArrayLayout* mpVertexArrayLayout = nullptr;
};

CREATE(CSandbox)