#version 430 core
#define TAU (1.570763f)
#define PI (3.14159)
#define TWO_PI (2 * PI)

layout(points) in;
layout(line_strip, max_vertices = 200) out;

uniform mat4 World;
uniform mat4 View;
uniform mat4 Projection;
uniform mat4 InverseProjection;
uniform vec2 FramebufferSize;
uniform vec3 ViewPosition;

uniform float NearClip;
uniform float FarClip;

in vec4 vPosition[];
in float vRadius[];

out vec4 gColor;

#define PLOT_SCALE (1.f)
#define PLOT_OFFSET (vec2(0,-PLOT_SCALE / 2))

//#define PLOT_OFFSET (vec2(0,0))
#define ASPECT_RATIO (FramebufferSize.x / FramebufferSize.y)

vec3 RotateZ(vec3 p, float theta)
{
	vec3 p1;

	float cosTheta = cos(theta);
	float sinTheta = sin(theta);

	p1.x = p.x * cosTheta - p.y * sinTheta;
	p1.y = p.x * sinTheta + p.y * cosTheta;
	p1.z = p.z;

	return p1;
}

vec2 RotateZ(vec2 p, float theta)
{
	vec2 p1;

	float cosTheta = cos(theta);
	float sinTheta = sin(theta);

	p1.x = p.x * cosTheta - p.y * sinTheta;
	p1.y = p.x * sinTheta + p.y * cosTheta;

	return p1;
}

float DistanceToBox(vec3 p, vec3 boxMin, vec3 boxMax)
{
	vec3 d;
	d.x = max(max(boxMin.x - p.x, 0), p.x - boxMax.x);
	d.y = max(max(boxMin.y - p.y, 0), p.y - boxMax.y);
	d.z = max(max(boxMin.z - p.z, 0), p.z - boxMax.z);

	return length(d);
}

bool ShouldCull(vec3 center, float radius)
{
	mat4 inverseProjection = inverse(Projection);
	/// direction vectors to the corners of the frustum
	vec3 corners[4];

	corners[0] = (inverseProjection * vec4(-1,+1,1,1)).xyz;
	corners[1] = (inverseProjection * vec4(+1,+1,1,1)).xyz;
	corners[2] = (inverseProjection * vec4(+1,-1,1,1)).xyz;
	corners[3] = (inverseProjection * vec4(-1,-1,1,1)).xyz;

	vec3 normals[4];


	for(int i =0 ; i < 4; ++i)
	{
		vec3 v0 = corners[i % 4];
		vec3 v1 = corners[(i + 1) % 4];

		vec3 normal = normalize(cross(v0,v1));
		float distanceToPlane = dot(center,normal) + radius;
		if (distanceToPlane < 0)
			return true;
	}

	return false;

}




/// <summary>
/// returns the screen-space (normalized device coordinates) bounds of a projected sphere
/// </summary>
/// <param name="center">view-space center of the sphere</param>
/// <param name="radius">world or view space radius of the sphere</param>
/// <param name="boxMin">minimum (bottom left) projected bounds</param>
/// <param name="boxMax">maximum (top right) projected bounds</param>
/// <returns>true if box is in the view volume</returns>
bool GetProjectedBounds(vec3 center, float radius, inout vec3 boxMin, inout vec3 boxMax)
{
	/// NO idea why this is necessary. :(
	radius /= PI;

	/// already in world coordinates. 
	center = (View * vec4(center,1)).xyz;

	if (ShouldCull(center,radius))
		return false;


	float d2 = dot(center,center);

	float a = sqrt(d2 - radius * radius);

	vec3 right = (radius / a) * vec3(-center.z, 0, center.x);
	vec3 up = vec3(0,radius,0);

	vec4 projectedRight  = Projection * vec4(right,0);
	vec4 projectedUp     = Projection * vec4(up,0);

	vec4 projectedCenter = Projection * vec4(center,1);
	projectedCenter.z = 0;

	vec4 north  = projectedCenter + projectedUp;
	vec4 east   = projectedCenter + projectedRight;
	vec4 south  = projectedCenter - projectedUp;
	vec4 west   = projectedCenter - projectedRight;

	//if (north.w < 0 && south.w < 0 && east.w < 0 && west.w < 0)
	//	return false;

	north /= north.w ;
	east  /= east.w  ;
	west  /= west.w  ;
	south /= south.w ;

	boxMin = min(min(min(east,west),north),south).xyz;
	boxMax = max(max(max(east,west),north),south).xyz;

	boxMin = clamp(boxMin, -1000, 1000);
	boxMax = clamp(boxMax, -1000, 1000);

	boxMin.z = 0;
	boxMax.z = 0;


	return true;
}



void Arrow(vec2 from, vec2 to, float length, vec4 color)
{
	gColor = color;//to.y < 0.f ? vec4(1,0,0,1) : vec4(0,1,0,1);


	to = from + normalize(to - from) * length;

	gl_Position = vec4(from,0,1); EmitVertex();
	gl_Position = vec4(to,0,1); EmitVertex();

	EndPrimitive();

	vec2 dir = normalize(to - from);
	vec2 head1 = to + 0.1f * length * RotateZ(-dir, TAU / 2.f);
	vec2 head2 = to + 0.1f * length * RotateZ(-dir, -TAU / 2.f);

	gl_Position = vec4(head1,0,1); EmitVertex();
	gl_Position = vec4(to,0,1); EmitVertex();
	gl_Position = vec4(head2,0,1); EmitVertex();

	EndPrimitive();

}

void TestQuad(vec3 center, float radius)
{
	vec3 boxMin, boxMax;

	if(!GetProjectedBounds(center, radius, boxMin, boxMax))
		return;



	vec3 projectedCenter = (boxMin + boxMax) * 0.5f;


	vec4 corners[4];

	corners[0] = vec4(boxMax.xy, boxMin.z, 1);
	corners[1] = vec4(boxMax.x, boxMin.yz, 1);
	corners[2] = vec4(boxMin.xy, boxMin.z, 1);
	corners[3] = vec4(boxMin.x, boxMax.yz, 1);

	vec4 colors[4];

	colors[0] = vec4(1,0,0,1);
	colors[1] = vec4(0,1,0,1);
	colors[2] = vec4(0,0,1,1);
	colors[3] = vec4(0,1,1,1);

	int order[6];

	order[0] = 0;
	order[1] = 1;
	order[2] = 2;
	order[3] = 0;
	order[4] = 3;
	order[5] = 2;

	for(int i = 0; i < 6; ++i)
	{
		int index = order[i];
		gColor = colors[index % 4];
		gl_Position = corners[index % 4];
		EmitVertex();
	}

	EndPrimitive();
}



void TestCircle(vec3 center, float radius)
{
	gColor = vec4(1,1,0,1);
	center = (View * vec4(center,1)).xyz;
	vec3 right = cross(vec3(0,1,0),normalize(center));

	const int sides = 16;
	float dTheta = TWO_PI / sides;

	for(float theta = 0; theta <= TWO_PI; theta += dTheta)
	{

		vec3 p = center + radius * vec3(cos(theta),sin(theta),0);

		gl_Position = Projection * vec4(p,1);
		EmitVertex();
	}

	EndPrimitive();

}



void DrawCompass(vec3 center, float radius)
{
	vec4 p = Projection * View * vec4(center, 1);

	Arrow(vec2(0),normalize(p.xz),0.4f,vec4(1,0,0,1));
}



void main(void)
{
	vec3 worldCenter = vPosition[0].xyz;
	float radius = vRadius[0];

	TestQuad(worldCenter, radius);
	TestCircle(worldCenter, radius / PI);

	//DrawCompass(worldCenter, radius);

}