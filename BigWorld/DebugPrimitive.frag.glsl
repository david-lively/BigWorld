#version 430 core
/// see http://www.lighthouse3d.com/cg-topics/code-samples/opengl-3-3-glsl-1-5-sample/

in vec4 gColor;
//in vec2 gTexCoord;
out vec4 fragmentColor;

void main() {
    fragmentColor = gColor;//vec4(1, 0, 0, 1);
}