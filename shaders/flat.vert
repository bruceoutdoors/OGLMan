#version 130

in vec4 vertexPositionModel;
in vec3 vertexColor;
in vec2 vertexUV;

uniform mat4 modelToProjectionMatrix;

out vec3 vertcolor;
out vec2 UV;

void main()
{
    gl_Position = modelToProjectionMatrix * vertexPositionModel;
    vertcolor = vertexColor;

    UV = vertexUV;
}
