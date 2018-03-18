#include "IndexedRenderer.h"

#include "Mesh.h"


IndexedRenderer::IndexedRenderer() {
}


IndexedRenderer::~IndexedRenderer() {
}

void IndexedRenderer::uploadMeshes(std::vector<std::reference_wrapper<Mesh>> meshes) {
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	std::vector<Vertex> vertexData;
	std::vector<unsigned int> indexData;
	int numVertexes = 0;
	int numIndexes = 0;
	for (auto mesh : meshes) {
		//record indexes for rendering
		UploadedMesh uploaded;
		uploaded.count = mesh.get().numVertices;
		uploaded.baseVertex = numVertexes;
		uploaded.offset = numIndexes;
		//add the data to the upload buffers
		vertexData.insert(vertexData.end(), mesh.get().vertexData.begin(), mesh.get().vertexData.end());
		indexData.insert(indexData.end(), mesh.get().indexData.begin(), mesh.get().indexData.end());
		m_uploaded[mesh.get().name] = uploaded;
		numVertexes += mesh.get().numVertices;
		numIndexes += mesh.get().numIndices;
	}
}

void IndexedRenderer::createVao() {
	//create buffers
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ibo);
	//create vao
	glCreateVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	//set up vertex attribs
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, pos));
	glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, norm));
	//cleanup
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
