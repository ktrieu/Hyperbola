#pragma once

#include <unordered_map>
#include <string>
#include <filesystem>
#include <fstream>

#include "GL\gl3w.h"

#include "Mesh.h"
#include "shader\Shader.h"

namespace fs = std::experimental::filesystem;

class ResourceLoader {

public:
	ResourceLoader();
	~ResourceLoader();

	void loadAll();

	Mesh& getMesh(std::string& name);

private:
	std::unordered_map<std::string, Mesh> m_meshes;
	std::unordered_map<std::string, Shader> m_shaders;

	void loadShader(std::ifstream& is, std::string& name, GLenum type);
	void load(fs::path path);
};

