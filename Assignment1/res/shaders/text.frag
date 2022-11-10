#version 420 core

in vec2 TexCoords;

out vec4 color;

uniform sampler2D Texture;
uniform vec4 Color;

void main(){
	vec4 sampled = vec4(1.0, 1.0, 1.0, texture(Texture, TexCoords).r);
    color = Color * sampled;
}