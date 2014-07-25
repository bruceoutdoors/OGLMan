#version 430

in vec3 vertexPositionWorld;
in vec3 color;
in vec3 N;

uniform vec3 lightPosition;
uniform vec3 eyePositionWorld;
uniform vec4 ambientLight;
uniform bool hasColor;

void main()
{
    vec3 L = normalize(lightPosition - vertexPositionWorld);
    vec3 V = normalize(eyePositionWorld - vertexPositionWorld);

    vec4 diffuseLight;
    vec4 specularLight;

    // diffuse light:
    float I_d = dot(L, N);


    // ** phong specular **
    vec3 R = dot(2*N, L)*N-L;
    float I_s = pow(dot(V, R), 50);

    // ** simplified phong specular **
//    vec3 H = normalize(L+V);
//    float I_s = pow(dot(N, H), 60);

    if (hasColor) {
        diffuseLight = vec4(vec3(I_d) * color, 1);
        specularLight = vec4(vec3(I_s) * color, 1);
    } else {
        diffuseLight = vec4(vec3(I_d), 1);
        specularLight = vec4(vec3(I_s), 1);
    }

    gl_FragColor = ambientLight + clamp(diffuseLight, 0, 1) + clamp(specularLight, 0, 1);
}
