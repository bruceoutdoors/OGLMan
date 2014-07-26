#version 430

in layout(location = 0) vec4 vertexPositionModel;
in layout(location = 1) vec3 vertexColor;

uniform mat4 modelToProjectionMatrix;

out vec3 vertcolor;

void main()
{
    gl_Position = modelToProjectionMatrix * vertexPositionModel;
    vertcolor = vertexColor;
}
