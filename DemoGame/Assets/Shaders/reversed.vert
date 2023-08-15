#version 330 core
layout (location = 0) in vec4 coVertex;

out vec2 coTexCoords;

uniform mat4 coModel;
uniform mat4 coProjection;

void main()
{
	coTexCoords = coVertex.zw;
	gl_Position = coProjection * coModel * vec4(coVertex.xy, 0.0, 1.0);
}