#pragma once

#include <unordered_map>
#include <string>
#include <filesystem>

#include "Mesh.h"

namespace fs = std::experimental::filesystem;

class ResourceLoader {

public:
	ResourceLoader();
	~ResourceLoader();

	void loadAll();

	Mesh& getMesh();

private:
	std::unordered_map<std::string, Mesh> m_meshes;

	void load(fs::path path);
};

