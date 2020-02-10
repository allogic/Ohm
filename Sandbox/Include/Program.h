#pragma once

#include <string>
#include <cstring>

#include "Ram.h"

class CProgram final {
public:
	CProgram(CRam& ram) : mRam(ram) {
		mProgram.resize(CRam::RomSize);
	};
	CProgram(const CProgram&) = delete;
	CProgram(CProgram&&) = delete;

public:
	auto& operator =(const CProgram&) = delete;

public:
	void Debug() {
		ImGui::SetNextWindowViewport(ImGui::GetID("Root"));
		ImGui::Begin("Program");
		ImGuiDockNodeFlags dockSpaceFlags = ImGuiDockNodeFlags_None;
		dockSpaceFlags |= ImGuiDockNodeFlags_PassthruCentralNode;

		if (ImGui::Button("Load"))
			mCompileStatus = mRam.Load(&mProgram[0], static_cast<unsigned int>(mProgram.size()));

		if (!mCompileStatus) {
			ImGui::SameLine();
			ImGui::Text("Failed compilation");
		}

		ImGui::InputTextMultiline("", &mProgram[0], mProgram.size());
		ImGui::End();
	}

private:
	CRam& mRam;

	bool mCompileStatus = true;

	std::string mProgram;
};