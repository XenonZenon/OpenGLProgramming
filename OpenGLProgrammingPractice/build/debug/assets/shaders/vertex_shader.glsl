#version 330 core

layout (location = 0) in vec4 position;
layout (location = 2) in vec2 texcoord;

out vec2 texcoordinate;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;
uniform mat4 transform;

void main(){
  gl_Position = projection * view * model * transform * position;
  texcoordinate = vec2(texcoord.x, 1.0 - texcoord.y);

};
