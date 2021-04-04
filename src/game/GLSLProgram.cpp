#include "Errors.h"
#include <GLSLProgram.h>
#include <fstream>
#include <vector>

GLSLProgram::GLSLProgram()
    : _numAttributes(0), _programID(0), _vertexShaderID(0),
      _fragmentShaderID(0) {}

GLSLProgram::~GLSLProgram() {}

void GLSLProgram::compileShaders(const std::string &vertexShaderFilePath,
                                 const std::string &fragmentShaderFilePath) {

  // Now time to link them together into a program.
  // Get a program object.
  _programID = glCreateProgram();

  _vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
  if (_vertexShaderID == 0) {
    fatalError("Failed to Create Vertex Shader!");
  }

  _fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
  if (_fragmentShaderID == 0) {
    fatalError("Failed to Create Fragment Shader!");
  }

  compileShader(vertexShaderFilePath, _vertexShaderID);
  compileShader(fragmentShaderFilePath, _fragmentShaderID);
}

void GLSLProgram::compileShader(const std::string &filePath, GLuint id) {

  // Open Vertex Shader File
  std::ifstream ShaderFile(filePath);
  if (ShaderFile.fail()) {
    perror(filePath.c_str());
    fatalError("Failed to open" + filePath);
  }

  // Read Vertex Shader File contents
  std::string fileContents = "";
  std::string line;
  while (std::getline(ShaderFile, line)) {
    fileContents += line;
    fileContents += "\n";
  }
  ShaderFile.close();

  const char *contentsPtr = fileContents.c_str();
  glShaderSource(id, 1, &contentsPtr, nullptr);

  glCompileShader(id);

  // Check the status of Shader Compilation
  GLint isCompiled = 0;
  glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);

  if (isCompiled == GL_FALSE) {
    GLint maxLength = 0;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

    // The maxLength includes the NULL character
    std::vector<GLchar> errorLog(maxLength);
    glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

    // Provide the infolog in whatever manor you deem best.
    // Exit with failure.
    glDeleteShader(id); // Don't leak the shader.

    std::printf("%s", &(errorLog[0]));
    fatalError("Shader " + filePath + " Compilation failed");
  }
}

void GLSLProgram::linkShaders() {

  // Vertex and fragment shaders are successfully compiled.

  // Attach our shaders to our program
  glAttachShader(_programID, _vertexShaderID);
  glAttachShader(_programID, _fragmentShaderID);

  // Link our program
  glLinkProgram(_programID);

  // Note the different functions here: glGetProgram* instead of glGetShader*.
  GLint isLinked = 0;
  glGetProgramiv(_programID, GL_LINK_STATUS, (int *)&isLinked);
  if (isLinked == GL_FALSE) {
    GLint maxLength = 0;
    glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

    // The maxLength includes the NULL character
    std::vector<GLchar> errorLog(maxLength);
    glGetProgramInfoLog(_programID, maxLength, &maxLength, &errorLog[0]);

    // We don't need the program anymore.
    glDeleteProgram(_programID);
    // Don't leak shaders either.
    glDeleteShader(_vertexShaderID);
    glDeleteShader(_fragmentShaderID);

    // Use the infoLog as you see fit.
    // In this simple program, we'll just leave
    std::printf("%s", &(errorLog[0]));
    fatalError("Shader linking failed");
  }

  glDetachShader(_programID, _vertexShaderID);
  glDetachShader(_programID, _fragmentShaderID);
  glDeleteShader(_vertexShaderID);
  glDeleteShader(_fragmentShaderID);
}

void GLSLProgram::addAttribute(const std::string &attributeName) {

  glBindAttribLocation(_programID, _numAttributes++, attributeName.c_str());
}

GLuint GLSLProgram::getUniformLocation(const std::string &uniformName) {

  GLuint location = glGetUniformLocation(_programID, uniformName.c_str());
  if (location == GL_INVALID_INDEX) {
    fatalError("Unifrom " + uniformName + " not found in shader!");
  }
  return location;
}

void GLSLProgram::use() {

  glUseProgram(_programID);

  for (int i = 0; i < _numAttributes; i++) {
    glEnableVertexAttribArray(i);
  }
}

void GLSLProgram::unuse() { glUseProgram(0); }