#version 430

in layout(location = 0) vec4 vertexPositionModel;
in layout(location = 1) vec3 vertexColor;
in layout(location = 2) vec3 normalModel;

uniform mat4 modelToProjectionMatrix;
uniform mat4 modelToWorldMatrix;
uniform mat4 normalMatrix;

out vec3 vertexPositionWorld;
out vec3 vertcolor;
out vec3 N;

void main()
{
    gl_Position = modelToProjectionMatrix * vertexPositionModel;
    vertexPositionWorld = vec3(modelToWorldMatrix * vertexPositionModel);
    N = normalize(vec3(normalMatrix * vec4(normalModel, 0.0f)));
    vertcolor = vertexColor;
}
