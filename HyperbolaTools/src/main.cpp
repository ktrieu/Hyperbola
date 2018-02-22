#include <iostream>
#include <filesystem>
#include <map>

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

void copyResources() {
	for (auto resource : resources) {
		//create any subdirectories if they don't exist
		if (!fs::exists(resource.second.parent_path())) {
			fs::create_directories(resource.second.parent_path());
		}
		fs::copy_file(resource.first, resource.second, fs::copy_options::overwrite_existing);
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
	copyResources();
	return 0;
}