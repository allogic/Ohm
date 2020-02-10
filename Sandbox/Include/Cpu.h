#pragma once

#include <vector>

#include "Ram.h"

enum OpCode : unsigned char {
	NOP = 0,
	JMP = 1,
	RET = 2,
	LDX = 3,
	LDY = 4,
	STA = 5,
	ADD = 6,
	SUB = 7,
	STX = 8,
	STY = 9,
	HLT = 255,
};

class CCpu final {
public:
	CCpu(CRam& CRam) : mRam(CRam) {}
	CCpu(const CCpu&) = delete;
	CCpu(CCpu&&) = delete;

public:
	auto& operator =(const CCpu&) = delete;

public:
	void Reset() {
		mPc = 0;
		mSp = CRam::StackOffset;

		mOp = 0;

		mRx = 0;
		mRy = 0;

		mAcc = 0;
	}
	void Update() {
		if (!mLoop) return;

		Clock();
	}
	void Clock() {
		Fetch();

		if (mInstructions[mOp].op)
			(this->*mInstructions[mOp].op)();
	}
	void Debug() {
		ImGui::Begin("Cpu");
		if (ImGui::Button("Reset"))	Reset();
		ImGui::Checkbox("Loop", &mLoop);
		if (ImGui::Button("Step")) Clock();
		ImGui::End();
	}

private:
	unsigned char Fetch() { return mOp = mRam[mPc++]; }

	void JMP() {
		// stack push
		mPc = Fetch();
	}
	void RET() {
		// stack pop
	}
	void LDX() {
		mRx = mRam[mSp + Fetch()];
	}
	void LDY() {
		mRy = mRam[mSp + Fetch()];
	}
	void STA() {
		mRam[mSp + Fetch()] = mAcc;
	}
	void ADD() {
		mAcc = mRx + mRy;
	}
	void SUB() {
		mAcc = mRx - mRy;
	}
	void STX() {
		mRam[mSp + Fetch()] = mRx;
	}
	void STY() {
		mRam[mSp + Fetch()] = mRy;
	}

private:
	CRam& mRam;

	unsigned int mPc = 0;
	unsigned int mSp = CRam::StackOffset;

	unsigned char mOp = 0;

	unsigned char mRx = 0;
	unsigned char mRy = 0;

	unsigned char mAcc = 0;

	bool mLoop = false;

	struct TInstruction {
		const char* name;
		void (CCpu::* op)();
	};

	std::vector<TInstruction> mInstructions{
		{"NOP", nullptr},
		{"JMP", &CCpu::JMP},
		{"RET", &CCpu::RET},
		{"LDX", &CCpu::LDX},
		{"LDY", &CCpu::LDY},
		{"STA", &CCpu::STA},
		{"ADD", &CCpu::ADD},
		{"SUB", &CCpu::SUB},
		{"STX", &CCpu::STX},
		{"STY", &CCpu::STY},
		{"HLT", nullptr},
	};
};