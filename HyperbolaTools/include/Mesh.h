#pragma once

#include <vector>
#include <string>

struct Mesh {
	int numVertices;
	std::vector<float> vertexData;
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