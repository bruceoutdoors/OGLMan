varying vec3 vertexPositionWorld;
varying vec3 vertcolor;
varying vec3 N;
varying vec2 UV;

uniform vec3 lightPosition;
uniform vec3 eyePositionWorld;
uniform vec4 ambientLight;
uniform vec3 flatColor;

uniform bool hasVertexColor;
uniform bool hasFlatColor;
uniform bool hasTexture;

uniform sampler2D textureSampler;

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

    if (hasTexture) {
      vec4 texcolor = texture2D(textureSampler, UV).rgba;
      diffuseLight = I_d * texcolor;
      specularLight = I_s * texcolor;
    } else if (hasVertexColor) {
        diffuseLight = vec4(I_d * vertcolor, 1);
        specularLight = vec4(I_s * vertcolor, 1);
    } else if (hasFlatColor) {
        diffuseLight = vec4(I_d * flatColor, 1);
        specularLight = vec4(I_s * flatColor, 1);
    } else {
        diffuseLight = vec4(vec3(I_d), 1);
        specularLight = vec4(vec3(I_s), 1);
    }

    gl_FragColor = ambientLight + clamp(diffuseLight, 0, 1) + clamp(specularLight, 0, 1);
}
