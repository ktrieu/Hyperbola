#pragma once

#include <vector>
#include <string>

#include <glm\glm.hpp>

struct Vertex {
	glm::vec3 pos;
	glm::vec3 norm;

	template <class Archive>
	void serialize(Archive& ar) {
		ar(pos.x);
		ar(pos.y);
		ar(pos.z);
		ar(norm.x);
		ar(norm.y);
		ar(norm.z);
	}
};

struct Mesh {
	int numVertices;
	std::vector<Vertex> vertexData;
	int numIndices;
	std::vector<unsigned int> indexData;
	std::string name;

	template <class Archive>
	void serialize(Archive& ar) {
		ar(numVertices);
		ar(vertexData);
		ar(numIndices);
		ar(indexData);
	}
};