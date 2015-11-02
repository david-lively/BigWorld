#version 430 core
/// http://www.lighthouse3d.com/cg-topics/code-samples/opengl-3-3-glsl-1-5-sample/

uniform mat4 World;
uniform mat4 View;
uniform mat4 Projection;

in vec3 Position;
in float Radius;

out vec4 vPosition;
out float vRadius;

void main()
{
	vPosition = vec4(Position,1);
	vRadius = Radius;
	gl_Position = vPosition;
}

