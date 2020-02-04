#include <glad/glad.h>

#include "VertexArrayLayout.h"

Ohm::CVertexArrayLayout::CVertexArrayLayout(const TVboLayout& attributes, const TEboLayout& indices) {
	glGenVertexArrays(1, &mVao);

	mAttribSize = static_cast<unsigned int>(attributes.size());
	mIndicesSize = static_cast<unsigned int>(indices.size());

	mVbos.resize(mAttribSize);

	glGenBuffers(mAttribSize, &mVbos[0]);
	glGenBuffers(1, &mEbo);

	glBindVertexArray(mVao);

	for (const auto& attribute : attributes) {
		glBindBuffer(GL_ARRAY_BUFFER, mVbos[attribute.index]);
		glBufferData(GL_ARRAY_BUFFER, attribute.data.size() * attribute.stride * sizeof(float), &attribute.data[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(attribute.index);
		glVertexAttribPointer(attribute.index, attribute.stride, GL_FLOAT, false, attribute.stride * sizeof(float), nullptr);
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Ohm::CVertexArrayLayout::~CVertexArrayLayout() {
	if (mAttribSize) glDeleteBuffers(mAttribSize, &mVbos[0]);
	if (mEbo)	glDeleteBuffers(1, &mEbo);

	glDeleteVertexArrays(1, &mVao);
}

void Ohm::CVertexArrayLayout::Bind() const {
	glBindVertexArray(mVao);
}

void Ohm::CVertexArrayLayout::Draw() const {
	glDrawElements(GL_TRIANGLES, mIndicesSize, GL_UNSIGNED_INT, nullptr);
}