#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in mat4 modle_mat;
uniform mat4  pv;
out vec2 TexCoord;
void main(){
	gl_Position = pv * modle_mat * vec4(aPos.x, aPos.y, aPos.z, 1.0);
	TexCoord=aTexCoord;
}