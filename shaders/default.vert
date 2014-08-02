#version 130

in vec4 vertexPositionModel;
in vec3 vertexColor;
in vec3 normalModel;
in vec2 vertexUV;

uniform mat4 modelToProjectionMatrix;
uniform mat4 modelToWorldMatrix;
uniform mat4 normalMatrix;

out vec3 vertexPositionWorld;
out vec3 vertcolor;
out vec3 N;
out vec2 UV;

void main()
{
    gl_Position = modelToProjectionMatrix * vertexPositionModel;
    vertexPositionWorld = vec3(modelToWorldMatrix * vertexPositionModel);
    N = normalize(vec3(normalMatrix * vec4(normalModel, 0.0f)));
    vertcolor = vertexColor;

    UV = vertexUV;
}
