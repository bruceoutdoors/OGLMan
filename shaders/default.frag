#version 430

out vec4 color;

in vec3 N;
in vec3 L;
in vec3 V;

uniform vec4 ambientLight;

void main()
{
    // diffuse light:
    float I_d = dot(L, N);
    vec4 diffuseLight = vec4(I_d, I_d, I_d, 1.0);

    // ** phong specular **
    vec3 R = dot(2*N, L)*N-L;
    float I_s = pow(dot(V, R), 50);

    // ** simplified phong specular **
//    vec3 H = normalize(L+V);
//    float I_s = pow(dot(N, H), 60);

    vec4 specularLight = vec4(I_s, I_s, I_s, 1);

    color = ambientLight + clamp(diffuseLight, 0, 1) + clamp(specularLight, 0, 1);
}
