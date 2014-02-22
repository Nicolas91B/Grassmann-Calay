#version 330 core
in vec4 Normal;
out vec4 gl_FragColor;


void main() {
	gl_FragColor = Normal;
}