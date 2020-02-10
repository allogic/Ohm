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
	CSandbox() :
		mProgram(mRam),
		mCpu(mRam),
		CApplication({ 60, false }, { 4, 0, 0, 1280, 720, "Demo" }) {
		PushScene();
	}

public:
	void OnUpdate(double deltaTime) override {
		ImGui::Button("I am docked");
		//ImGui::ShowDemoWindow();

		mRam.Hexdump("Rom", CRam::RomOffset, CRam::RomSize);
		mRam.Hexdump("Heap", CRam::HeapOffset, CRam::HeapSize);
		mRam.Hexdump("Stack", CRam::StackOffset, CRam::StackSize);

		mRam.Debug();
		mProgram.Debug();
		mCpu.Debug();
	}

	void OnFixedUpdate(double deltaTime) override {
		mCpu.Update();
	}

private:
	CRam mRam;
	CProgram mProgram;
	CCpu mCpu;
};

CREATE(CSandbox)