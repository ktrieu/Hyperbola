#pragma once

#include "resource\ResourceLoader.h"
#include "render\IndexedRenderer.h"

struct GLFWwindow;

class App
{
public:
	App();
	~App();

	void init();
	void run();

private:
	int m_height = 720;
	int m_width = 1080;

	GLFWwindow* m_window;

	ResourceLoader m_resLoader;
	IndexedRenderer m_renderer;

};

