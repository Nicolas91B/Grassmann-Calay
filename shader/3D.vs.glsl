#version 330 core
layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexNormal;
out vec4 Normal;
out vec3 Position_vs;


uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uNormalMatrix;


void main() {
	Normal = vec4(aVertexNormal, 0);
	gl_Position = uMVPMatrix * vec4(aVertexPosition, 1);
	Position_vs = vec3(uMVMatrix * vec4(aVertexPosition, 1));
}