#include <Ohm.h>

#include "Program.h"
#include "Ram.h"
#include "Cpu.h"

using namespace Ohm;

const unsigned char countProgram[128] = {
	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	LDX, 0,	LDY, 1,	ADD, STA, 0, JMP, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

class CSandbox final : public CApplication {
public:
	CSandbox() : mProgram(mRam), mCpu(mRam), CApplication({ 1000, 1280, 720, false, "Demo" }) {
		PushScene();
	}

public:
	void OnUpdate(double deltaTime) override {
		ImGui::ShowDemoWindow();

		mRam.Hexdump("Rom", CRam::RomOffset, CRam::RomSize);
		mRam.Hexdump("Heap", CRam::HeapOffset, CRam::HeapSize);
		mRam.Hexdump("Stack", CRam::StackOffset, CRam::StackSize);

		mProgram.Debug();
		mRam.Debug();
		mCpu.Debug();
	}

	void OnFixedUpdate(double deltaTime) override {
		mCpu.Update();
	}

private:
	CProgram mProgram;
	CRam mRam;
	CCpu mCpu;
};

CREATE(CSandbox)