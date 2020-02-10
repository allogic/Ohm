#pragma once

#include <cstring>
#include <sstream>

class CRam final {
public:
	static const unsigned int RamSize = 512;

	static const unsigned int RomOffset = 0;
	static const unsigned int RomSize = 128;
	static const unsigned int RomProgramStart = 16;

	static const unsigned int HeapOffset = 128;
	static const unsigned int HeapSize = 256;

	static const unsigned int StackOffset = 384;
	static const unsigned int StackSize = 128;

public:
	CRam() : mpData(new unsigned char[RamSize]) {
		std::memset(mpData, 0, RamSize);
	}
	CRam(const CRam&) = delete;
	CRam(CRam&&) = delete;

	~CRam() { delete[] mpData; }

public:
	auto& operator =(const CRam&) = delete;
	auto& operator [](unsigned int i) { return mpData[i]; }

public:
	void Reset() {
		std::memset(&mpData[HeapOffset], 0, HeapSize);
		std::memset(&mpData[StackOffset], 0, StackSize);
	}
	bool Load(const char* program, unsigned int size) {
		if (size >= RomSize) return false;

		for (unsigned int i = 0; i < 16; i++)
			mpData[RomOffset + i] = program[i];

		for (unsigned int i = 0; i < RomSize - RomProgramStart; i++)
			mpData[RomOffset + RomProgramStart + i] = program[i];

		//for (unsigned int i = 0; i < RomSize; i++) {
		//	if (i < RomProgramStart) mpData[StackOffset + i] = program[i];
		//	else mpData[RomOffset - RomProgramStart + i] = program[i];
		//}

		return true;
	}
	void Debug() {
		ImGui::Begin("Ram");
		if (ImGui::Button("Reset")) Reset();
		ImGui::End();
	}
	void Hexdump(const char* title, unsigned int offset, unsigned int size) {
		ImGui::Begin(title);

		for (unsigned int i = offset; i < offset + size; i += 16) {
			ImGui::Text("0x%03X", i);
			ImGui::SameLine();

			for (unsigned int j = 0; j < 16; j++) {
				ImGui::Text("%02X", mpData[i + j]);
				ImGui::SameLine();
			}

			std::ostringstream oss;

			for (unsigned int j = 0; j < 16; j++)
				oss << static_cast<unsigned char>(mpData[i + j] >= 32 && mpData[i + j] < 127
					? mpData[i + j]
					: ' ');

			ImGui::Text(oss.str().c_str());
		}

		ImGui::End();
	}

private:
	unsigned char* mpData = nullptr;
};