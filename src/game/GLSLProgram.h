#pragma once

#include <GL/glew.h>
#include <string>

class GLSLProgram {

public:
  GLSLProgram();
  ~GLSLProgram();

  void compileShaders(const std::string &vertexShaderFilePath,
                      const std::string &fragmentShaderFilePath);

  void linkShaders();

  void addAttribute(const std::string &attributeName);

  GLuint getUniformLocation(const std::string &uniformName);

  void use();
  void unuse();

private:
  int _numAttributes;
  GLuint _programID;
  GLuint _vertexShaderID;
  GLuint _fragmentShaderID;

  void compileShader(const std::string &filepath, GLuint id);
};