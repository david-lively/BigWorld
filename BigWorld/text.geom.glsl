#version 410 core
/// Text renderer - see http://github.prideout.net/strings-inside-vertex-buffers/
layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

in int vCharacter[1];
in int vPosition[1];
out vec2 gTexCoord;
uniform sampler2D Sampler;

uniform vec2 CellSize;
uniform vec2 RenderSize;
uniform vec2 RenderOrigin;

void main()
{
    // Determine the final quad's position and size:
    float x = RenderOrigin.x + float(vPosition[0]) * RenderSize.x;
    float y = RenderOrigin.y;
    vec4 P = vec4(x, y, 0, 1);
    vec4 U = vec4(0.5, 0, 0, 0) * RenderSize.x;
    vec4 V = vec4(0, 0.5, 0, 0) * RenderSize.y;
    
    // Determine the texture coordinates:
    int letter = vCharacter[0] - 32;
    int row = letter / 16;
    int col = letter % 16;
    float S0 = CellSize.x * col;
    float T0 = CellSize.y * row;
    float S1 = S0 + CellSize.x;
    float T1 = T0 + CellSize.y;
    
    // Output the quad's vertices:
    gTexCoord = vec2(S0, T1); gl_Position = P-U-V; EmitVertex();
    gTexCoord = vec2(S1, T1); gl_Position = P+U-V; EmitVertex();
    gTexCoord = vec2(S0, T0); gl_Position = P-U+V; EmitVertex();
    gTexCoord = vec2(S1, T0); gl_Position = P+U+V; EmitVertex();
    EndPrimitive();
}