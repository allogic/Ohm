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
		const ImVec2 position{ ImGui::GetWindowPos().x,	ImGui::GetWindowPos().y, };
		const ImVec2 size{
			std::max(std::min(ImGui::GetWindowSize().x / 3, 300.f), 100.f),
			ImGui::GetWindowSize().y,
		};

		ImGui::SetNextWindowPos(position);
		ImGui::SetNextWindowSize(size);

		ImGuiWindowFlags windowFlags = ImGuiWindowFlags_None;
		windowFlags |= ImGuiWindowFlags_AlwaysAutoResize;
		windowFlags |= ImGuiWindowFlags_NoCollapse;
		windowFlags |= ImGuiWindowFlags_NoDocking;
		windowFlags |= ImGuiWindowFlags_NoScrollbar;
		windowFlags |= ImGuiWindowFlags_NoTitleBar;

		ImGui::Begin("Program", (bool*)1, windowFlags);

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