#version 330 core

layout (location = 0) in vec3 position;
layout (location = 2) in vec2 texcoord;

out vec2 texcoordinate;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){

  gl_Position = projection * model * view * vec4(position, 1.0f);
  texcoordinate = vec2(texcoord.x, 1.0 - texcoord.y);

};
