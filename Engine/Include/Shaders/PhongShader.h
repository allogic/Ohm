#pragma once

#include "../Core.h"

namespace Ohm::Shader {
	CShader* CreatePhongShader() {
		const std::string vertexSource = R"shader(
#version 460

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUv;

out VS_OUT {
	vec3 position;
	vec3 normal;
	vec2 uv;
} vsOut;

void main() {
	vsOut.position = aPosition;
	vsOut.normal = aNormal;
	vsOut.uv = aUv;

	gl_Position = vec4(aPosition, 1.);
}
		)shader";

		const std::string fragmentSource = R"shader(
#version 460

uniform sampler2D renderTexture;

in VS_OUT {
	vec3 position;
  vec3 normal;
	vec2 uv;
} vsIn;

out vec4 fragColor;

void main() {
	//fragColor = texture(renderTexture, vsIn.uv);
	fragColor = vec4(vsIn.uv, 0., 1.);
}
		)shader";

		auto* pPhongShader = new CShader;

		if (pPhongShader->Compile(vertexSource, fragmentSource)) return pPhongShader;

		ENGINE_TRACE("Failed compiling phong shader");

		return nullptr;
	}
}