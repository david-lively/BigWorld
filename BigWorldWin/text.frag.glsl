#version 410 core

/// Text renderer - see http://github.prideout.net/strings-inside-vertex-buffers/

out vec4 FragColor;
in vec2 gTexCoord;

uniform sampler2D Sampler;
uniform vec3 TextColor;

void main()
{
    float A = texture(Sampler, gTexCoord).r;
    FragColor = vec4(TextColor, A);
}