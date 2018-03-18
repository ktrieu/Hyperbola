#pragma once

#include <vector>
#include <unordered_map>

#include <gl\gl3w.h>

#include "Mesh.h"

struct UploadedMesh {
	unsigned int count;
	unsigned int offset;
	unsigned int baseVertex;
};

class IndexedRenderer {
public:
	IndexedRenderer();
	~IndexedRenderer();

	void createVao();
	void uploadMeshes(std::vector<std::reference_wrapper<Mesh>> meshes);

private:
	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ibo;

	std::unordered_map<std::string, UploadedMesh> m_uploaded;

};
