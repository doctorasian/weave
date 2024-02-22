#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>

class Shader {
public:
  u_int ID;
  void Load(std::string vertexPath, std::string fragmentPath);
  void Load(std::string vertexPath, std::string fragmentPath,
            std::string geometryPath);
  void Use();
  void SetBool(const std::string &name, bool value);
  void SetInt(const std::string &name, int value);
  void SetFloat(const std::string &name, float value);

private:
  void CheckCompileErrors(GLuint shader, std::string type);
};

#endif