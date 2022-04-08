#version 330 core

in vec3 vertexcolor;
in vec2 texcoordinate;

out vec4 fragcolor;

uniform sampler2D unitexture1;
uniform sampler2D unitexture2;

void main(){

  fragcolor = mix(texture(unitexture1, texcoordinate), texture(unitexture2, texcoordinate), 0.2);

};
