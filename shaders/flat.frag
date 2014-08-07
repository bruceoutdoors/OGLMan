#version 130

in vec3 vertcolor;
in vec2 UV;

uniform vec3 flatColor;
uniform vec3 wireframeColor;
uniform vec3 selectColor;

uniform bool hasVertexColor;
uniform bool hasFlatColor;
uniform bool hasTexture;
uniform bool hasWireframeMode;
uniform bool isSelectRender;

uniform sampler2D textureSampler;

void main()
{
    if (isSelectRender) {
        gl_FragColor = vec4(selectColor, 1.0);
    } else if (hasWireframeMode) {
        gl_FragColor = vec4(wireframeColor, 1.0);
    } else if (hasTexture) {
        gl_FragColor = texture2D(textureSampler, UV).rgba;
    } else if (hasVertexColor) {
        gl_FragColor = vec4(vertcolor, 1.0);
    } else if (hasFlatColor) {
        gl_FragColor = vec4(vec3(flatColor), 1.0);
    } else {
        gl_FragColor = vec4(1.0);
    }
}
