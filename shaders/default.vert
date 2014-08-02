attribute vec4 vertexPositionModel;
attribute vec3 vertexColor;
attribute vec3 normalModel;
attribute vec2 vertexUV;

uniform mat4 modelToProjectionMatrix;
uniform mat4 modelToWorldMatrix;
uniform mat4 normalMatrix;

varying vec3 vertexPositionWorld;
varying vec3 vertcolor;
varying vec3 N;
varying vec2 UV;

void main()
{
    gl_Position = modelToProjectionMatrix * vertexPositionModel;
    vertexPositionWorld = vec3(modelToWorldMatrix * vertexPositionModel);
    N = normalize(vec3(normalMatrix * vec4(normalModel, 0.0f)));
    vertcolor = vertexColor;

    UV = vertexUV;
}
