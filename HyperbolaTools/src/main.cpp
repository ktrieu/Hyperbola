#include <iostream>
#include <filesystem>

namespace fs = std::experimental::filesystem;

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
	return 0;
}