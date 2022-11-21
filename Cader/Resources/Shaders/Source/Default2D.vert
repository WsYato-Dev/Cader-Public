#version 450

const vec2 vertexPosition[4] =
{
	vec2(-0.5f, -0.5f),
	vec2(0.5f, -0.5f),
	vec2(0.5f, 0.5f),
	vec2(-0.5f, 0.5f)
};

struct Target
{
	vec4 color;
	vec2 position;
};

layout(std430, set = 0, binding = 0) readonly buffer TargetsSBO
{
	Target targets[];
};

layout(location = 0) out vec4 vColor;

void main()
{
	const Target target = targets[gl_InstanceIndex];

	vColor = target.color;
	gl_Position = vec4(vertexPosition[gl_VertexIndex] + target.position, 0.0f, 1.0f);
}