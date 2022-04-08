#version 400

in vec3 vertexcolor;
in vec2 texcoordinate;

out vec4 fragcolor;

uniform sampler2D unitexture;

void main(){

  fragcolor = texture(unitexture, texcoordinate);

};
