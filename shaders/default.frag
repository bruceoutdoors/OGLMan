#version 430

out vec4 color;

in vec3 vertexPositionWorld;
in vec3 N;

uniform vec3 lightPosition;
uniform vec3 eyePositionWorld;
uniform vec4 ambientLight;

void main()
{
    // diffuse light:
    vec3 L = normalize(lightPosition - vertexPositionWorld);
    float I_d = dot(L, N);
    vec4 diffuseLight = vec4(I_d, I_d, I_d, 1.0);

    vec3 V = normalize(eyePositionWorld - vertexPositionWorld);

    // ** phong specular **
    vec3 R = dot(2*N, L)*N-L;
    float I_s = pow(dot(V, R), 50);

    // ** simplified phong specular **
//    vec3 H = normalize(L+V);
//    float I_s = pow(dot(N, H), 60);


    vec4 specularLight = vec4(I_s, I_s, I_s, 1);

    color = ambientLight + clamp(diffuseLight, 0, 1) + clamp(specularLight, 0, 1);
}
