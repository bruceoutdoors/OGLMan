attribute vec4 vertexPositionModel;
attribute vec3 vertexColor;
attribute vec2 vertexUV;

uniform mat4 modelToProjectionMatrix;

varying vec3 vertcolor;
varying vec2 UV;

void main()
{
    gl_Position = modelToProjectionMatrix * vertexPositionModel;
    vertcolor = vertexColor;

    UV = vertexUV;
}
