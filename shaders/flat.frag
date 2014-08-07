#version 130

in vec3 vertcolor;
in vec2 UV;

uniform vec3 flatColor;

uniform bool hasVertexColor;
uniform bool hasFlatColor;
uniform bool hasTexture;

uniform sampler2D textureSampler;

void main()
{
    if (hasTexture) {
        gl_FragColor = texture2D(textureSampler, UV).rgba;
    } else if (hasVertexColor) {
        gl_FragColor = vec4(vertcolor, 1.0);
    } else if (hasFlatColor) {
        gl_FragColor = vec4(vec3(flatColor), 1.0);
    } else {
        gl_FragColor = vec4(1.0);
    }
}
