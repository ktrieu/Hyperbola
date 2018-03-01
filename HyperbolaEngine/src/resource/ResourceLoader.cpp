#include "ResourceLoader.h"

#include <fstream>

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

void ResourceLoader::load(fs::path path) {
	if (path.extension() == ".hmsh") {
		std::ifstream is(path, std::ios::binary);
		cereal::BinaryInputArchive archive(is);
		Mesh mesh;
		archive(mesh);
		m_meshes.insert(std::make_pair(getPathRelativeTo(path, fs::current_path()).string(), mesh));
	}
}