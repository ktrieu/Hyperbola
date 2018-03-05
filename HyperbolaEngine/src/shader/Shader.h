#pragma once

#include <gl\gl3w.h>
#include <iostream>
#include <string>

struct Shader {
	GLuint m_id;
	GLenum m_type;

	Shader(std::string& data, GLenum type) {
		m_type = type;
		m_id = glCreateShader(type);
		const char* dataPtr = data.c_str();
		glShaderSource(m_id, 1, &dataPtr, NULL);
		glCompileShader(m_id);
		GLint result;
		glGetShaderiv(m_id, GL_COMPILE_STATUS, &result);
		if (result != GL_FALSE) {
			//output a helpful info log
			GLint logLen;
			glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &logLen);
			std::string log;
			log.reserve(logLen);
			glGetShaderInfoLog(m_id, logLen, NULL, (GLchar*)log.data());
			std::cout << log << "\n";
		}
	}

};