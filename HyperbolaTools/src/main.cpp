#include <iostream>
#include <filesystem>
#include <map>
#include <fstream>

#include <cereal\cereal.hpp>
#include <cereal\archives\binary.hpp>
#include <cereal\types\vector.hpp>

#include <assimp\scene.h>
#include <assimp\Importer.hpp>
#include <assimp\postprocess.h>

#include "Mesh.h"

namespace fs = std::experimental::filesystem;

fs::path getPathRelativeTo(fs::path path, fs::path root) {
	auto pathIter = path.begin();
	auto rootIter = root.begin();
	//loop until we find the first different component
	while (*pathIter == *rootIter) {
		pathIter++;
		rootIter++;
	}
	fs::path relPath;
	while (pathIter != path.end()) {
		relPath.append(*pathIter);
		pathIter++;
	}
	return relPath;
}

std::map<fs::path, fs::path> resources;

void processBlend(fs::path from, fs::path to) {
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(from.string(), aiProcess_Triangulate);
	//just find the first mesh in the scene for now
	aiMesh* aiMesh = scene->mMeshes[0];
	Mesh mesh;
	mesh.numVertices = aiMesh->mNumVertices;
	mesh.numIndices = aiMesh->mNumFaces * 3;
	for (int i = 0; i < aiMesh->mNumVertices; i++) {
		aiVector3D vert = aiMesh->mVertices[i];
		aiVector3D normal = aiMesh->mNormals[i];
		mesh.vertexData.push_back(vert.x);
		mesh.vertexData.push_back(vert.y);
		mesh.vertexData.push_back(vert.z);
		mesh.vertexData.push_back(normal.x);
		mesh.vertexData.push_back(normal.y);
		mesh.vertexData.push_back(normal.z);
	}
	std::vector<unsigned int> indexes;
	for (int i = 0; i < aiMesh->mNumFaces; i++) {
		aiFace face = aiMesh->mFaces[i];
		mesh.indexData.push_back(face.mIndices[0]);
		mesh.indexData.push_back(face.mIndices[1]);
		mesh.indexData.push_back(face.mIndices[2]);
	}
	std::ofstream os(to.replace_extension("hmsh"), std::ios::binary);
	cereal::BinaryOutputArchive archive(os);
	archive(mesh);
}

void enumerateResources(fs::path resourcePath, fs::path outputPath) {
	fs::recursive_directory_iterator resourceIter(resourcePath);
	for (fs::path path : resourceIter) {
		//only process files
		if (fs::is_regular_file(path)) {
			fs::path relPath = getPathRelativeTo(path, resourcePath);
			fs::path resourceOutPath = outputPath / relPath;
			resources[path] = resourceOutPath;
		}
	}
}

void copyResource(fs::path from, fs::path to) {
	fs::path ext = from.extension();
	if (ext.string() == ".blend") {
		std::cout << "Post processing .blend: " << to.filename() << "\n";
		processBlend(from, to);
	}
	else {
		std::cout << "Copying " << to.filename() << "\n";
		fs::copy_file(from, to);
	}
}

void processResources() {
	for (auto resource : resources) {
		if (!fs::exists(resource.second)) {
			//create subdirectories
			fs::create_directories(resource.second.parent_path());
			copyResource(resource.first, resource.second);
		}
		else {
			//check timestamps to avoid unnnecessary copying
			fs::file_time_type resourceWriteTime = fs::last_write_time(resource.first);
			fs::file_time_type outWriteTime = fs::last_write_time(resource.second);
			if (resourceWriteTime > outWriteTime) {
				copyResource(resource.first, resource.second);
			}
		}
	}
}

int main(int argc, char** argv) {
	if (argc < 3) {
		std::cout << "Usage: HyperbolaTools.exe [resource folder] [output path]\n";
		return 1;
	}
	fs::path resourcePath(argv[1]);
	fs::path outputPath(argv[2]);
	std::cout << "== HyperbolaTools v1 ==\n";
	std::cout << "Resource folder is: " << resourcePath << "\n";
	std::cout << "Output folder is: " << outputPath << "\n";
	enumerateResources(resourcePath, outputPath);
	processResources();
	return 0;
}