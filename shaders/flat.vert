#version 430

in layout(location = 0) vec4 vertexPositionModel;
in layout(location = 1) vec3 vertexColor;
in layout(location = 3) vec2 vertexUV;

uniform mat4 modelToProjectionMatrix;

out vec3 vertcolor;
out vec2 UV;

void main()
{
    gl_Position = modelToProjectionMatrix * vertexPositionModel;
    vertcolor = vertexColor;

    UV = vertexUV;
}
