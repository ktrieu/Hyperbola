#include "ResourceLoader.h"

#include <fstream>
#include <string>

#include <cereal\cereal.hpp>
#include <cereal\archives\binary.hpp>
#include <cereal\types\vector.hpp>

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


ResourceLoader::ResourceLoader() {
}


ResourceLoader::~ResourceLoader() {
}

void ResourceLoader::loadAll() {
	fs::recursive_directory_iterator iter(fs::current_path());
	for (fs::path res : iter) {
		if (fs::is_regular_file(res)) {
			load(res);
		}
	}
}

void ResourceLoader::loadShader(std::ifstream& is, std::string& name, GLenum type) {
	is.seekg(std::ios::end);
	unsigned int len = is.tellg();
	is.seekg(std::ios::beg);
	std::string shaderData;
	shaderData.reserve(len);
	is.read((char*)shaderData.data(), len);
	Shader shader(shaderData, type);
	m_shaders.emplace(std::make_pair(name, shader));
}

void ResourceLoader::load(fs::path path) {
	std::string relPath = getPathRelativeTo(path, fs::current_path()).string();
	if (path.extension() == ".hmsh") {
		std::ifstream is(path, std::ios::binary);
		cereal::BinaryInputArchive archive(is);
		Mesh mesh;
		archive(mesh);
		mesh.name = relPath;
		m_meshes.insert(std::make_pair(relPath, mesh));
	}
	if (path.extension() == ".vert") {
		std::ifstream is(path);
		loadShader(is, relPath, GL_VERTEX_SHADER);
	}
	if (path.extension() == ".frag") {
		std::ifstream is(path);
		loadShader(is, relPath, GL_FRAGMENT_SHADER);
	}
}