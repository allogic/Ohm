#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Ohm::Components {
	class CTransform final {
	public:
		CTransform() = default;
		CTransform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale) :
			mPosition(position),
			mRotation(rotation),
			mScale(scale) {}

	public:
		glm::mat4 Model() const {
			glm::mat4 model;

			glm::translate(model, mPosition);

			glm::rotate(model, mRotation.x, { 1.f, 0.f, 0.f });
			glm::rotate(model, mRotation.y, { 0.f, 1.f, 0.f });
			glm::rotate(model, mRotation.z, { 0.f, 0.f, 1.f });

			glm::scale(model, mScale);

			return model;
		}

	private:
		glm::vec3 mPosition{ 0.f, 0.f, 0.f };
		glm::vec3 mRotation{ 0.f, 0.f, 0.f };
		glm::vec3 mScale{ 1.f, 1.f, 1.f };
	};
}