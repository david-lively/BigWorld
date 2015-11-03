#version 410 core

in vec4 vPosition;
in vec4 vColor;
//in vec2 gTexCoord;
out vec4 fragmentColor;

void main() {
//    fragmentColor = vColor;
    fragmentColor = vec4(vPosition.xyz,1);
}