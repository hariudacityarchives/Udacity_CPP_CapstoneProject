
#include "Vertex.h"
#include <Sprite.h>

Sprite::Sprite() : _vboID(0), _x(0.0f), _y(0.0f), _width(0.0f), _height(0.0f) {}

Sprite::~Sprite() {
  if (_vboID != 0) {
    glDeleteBuffers(1, &_vboID);
  }
}

// Vertex Buffer Object feature

void Sprite::init(float x, float y, float width, float height) {

  _x = x;
  _y = y;
  _width = width;
  _height = height;

  // Generate Vertex Object Buffer
  if (_vboID == 0) {
    glGenBuffers(1, &_vboID);
  }

  Vertex vertexData[6];

  // First Triangle
  vertexData[0].position.x = x + width;
  vertexData[0].position.y = y + height;

  vertexData[1].position.x = x;
  vertexData[1].position.y = y + height;

  vertexData[2].position.x = x;
  vertexData[2].position.y = y;

  // Second Triangle
  vertexData[3].position.x = x;
  vertexData[3].position.y = y;

  vertexData[4].position.x = x + width;
  vertexData[4].position.y = y;

  vertexData[5].position.x = x + width;
  vertexData[5].position.y = y + height;

  for (int i = 0; i < 6; i++) {
    vertexData[i].color.r = 255;
    vertexData[i].color.g = 0;
    vertexData[i].color.b = 255;
    vertexData[i].color.a = 255;
  }

  vertexData[1].color.r = 255;
  vertexData[1].color.g = 0;
  vertexData[1].color.b = 0;
  vertexData[1].color.a = 255;

  vertexData[4].color.r = 0;
  vertexData[4].color.g = 255;
  vertexData[4].color.b = 0;
  vertexData[4].color.a = 255;

  glBindBuffer(GL_ARRAY_BUFFER, _vboID);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::draw() {
  glBindBuffer(GL_ARRAY_BUFFER, _vboID);

  glEnableVertexAttribArray(0);

  // This Position Attribute Pointer
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void *)offsetof(Vertex, position));

  // This Color Attribute Pointer
  glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex),
                        (void *)offsetof(Vertex, color));

  glDrawArrays(GL_TRIANGLES, 0, 6);

  glDisableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
}