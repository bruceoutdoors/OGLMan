#version 430

in layout(location = 0) vec4 vertexPositionModel;
in layout(location = 1) vec3 vertexColor;
in layout(location = 2) vec3 normalModel;

uniform mat4 modelToProjectionMatrix;
uniform mat4 modelToWorldMatrix;
uniform mat4 normalMatrix;

uniform vec3 lightPosition;
uniform vec3 eyePositionWorld;

out vec3 N;
out vec3 L;
out vec3 V;

void main()
{
    gl_Position = modelToProjectionMatrix * vertexPositionModel;
    vec3 vertexPositionWorld = vec3(modelToWorldMatrix * vertexPositionModel);

    N = normalize(vec3(normalMatrix * vec4(normalModel, 0.0f)));
    L = normalize(lightPosition - vertexPositionWorld);
    V = normalize(eyePositionWorld - vertexPositionWorld);
}
