#pragma once

#include <vector>

struct Mesh {
	int numVertices;
	std::vector<float> vertexData;
	int numIndices;
	std::vector<float> indexData;

	template <class Archive>
	void serialize(Archive& ar) {
		ar(numVertices);
		ar(vertexData);
		ar(numIndices);
		ar(indexData);
	}
};