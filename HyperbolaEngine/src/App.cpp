#include "App.h"

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <iostream>

App::App() {

}

App::~App() {

}

void App::init() {
	if (!glfwInit()) {
		std::cout << "Failed to init GLFW.\n";
	}
	m_window = glfwCreateWindow(m_width, m_height, "Hyperbola", 0, 0);
	if (m_window == nullptr) {
		std::cout << "Failed to create window.\n";
	}
	glfwMakeContextCurrent(m_window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to load OpenGL.\n";
	}
	std::cout << "HyperbolaEngine: GL version: " << GLVersion.major << "." << GLVersion.minor << "\n";
}

void App::run() {
	while (!glfwWindowShouldClose(m_window)) {
		glfwPollEvents();
	}
}