#version 400
in vec3 vertex_point;
void main(){
  gl_Position = vec4(vertex_point, 1.0);
};
