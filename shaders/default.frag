#version 430

out vec4 color;

in vec3 vertexPositionWorld;
in vec3 normalWorld;

uniform vec3 lightPosition;
uniform vec3 eyePositionWorld;
uniform vec4 ambientLight;

void main()
{
    // diffuse light:
    vec3 lightVector = normalize(lightPosition - vertexPositionWorld);
    float brightness = dot(lightVector, normalWorld);
    vec4 diffuseLight = vec4(brightness, brightness, brightness, 1.0);

    // specular light:
    vec3 reflectedLightVectorWorld = reflect(-lightVector, normalWorld);
    vec3 eyeVectorWorld = normalize(eyePositionWorld - vertexPositionWorld);
    float s = dot(reflectedLightVectorWorld, eyeVectorWorld);
    s = pow(s, 50);
    vec4 specularLight = vec4(s, s, s, 1);

    color = ambientLight + clamp(diffuseLight, 0, 1) + clamp(specularLight, 0, 1);
}
