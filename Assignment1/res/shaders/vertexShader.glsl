#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 aColor;

out vec4 color_frag;
uniform mat4 Model;
uniform mat4 Projection;

void main() {	
	gl_Position = Projection * Model * vec4(aPos.x,aPos.y,aPos.z,1.0);	
	color_frag = aColor;
}