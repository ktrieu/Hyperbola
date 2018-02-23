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

void copyResource(fs::path from, fs::path to) {
	std::cout << "Copying " << to.filename() << "\n";
	fs::copy_file(from, to);
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