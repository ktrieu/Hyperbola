#include "App.h"

#include <gl\gl3w.h>
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
	if (gl3wInit() != 0) {
		std::cout << "Failed to init OpenGL.\n";
	}
	std::cout << "HyperbolaEngine: GL version: " << glGetString(GL_VERSION) << "\n";
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	std::cout << "Loading resources.\n";
	m_resLoader.loadAll();
	std::string mName("model\\fish.hmsh");
	std::vector<std::reference_wrapper<Mesh>> meshes;
	meshes.emplace_back(m_resLoader.getMesh(mName));
	m_renderer.createVao();
	m_renderer.uploadMeshes(meshes);
}

void App::run() {
	while (!glfwWindowShouldClose(m_window)) {
		glClear(GL_COLOR_BUFFER_BIT);
		glfwPollEvents();
		glfwSwapBuffers(m_window);
	}
}