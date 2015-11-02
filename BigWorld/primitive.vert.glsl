#version 410 core
uniform mat4 World;
uniform mat4 View;
uniform mat4 Projection;

in vec3 Position;
in vec4 Color;

out vec4 vPosition;
out vec4 vColor;

void main()
{
	//vPosition = Projection * View * World * vec4(Position,1);
    vPosition.z = 0.9f;
    vPosition = vec4(Position, 1);
    vColor = Color;
	gl_Position = vPosition;
}

