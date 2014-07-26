#version 430

in vec3 vertcolor;

uniform vec3 flatColor;

uniform bool hasVertexColor;
uniform bool hasFlatColor;

void main()
{
    if (hasVertexColor) {
        gl_FragColor = vec4(vertcolor, 1.0);
    } else if (hasFlatColor) {
        gl_FragColor = vec4(vec3(flatColor), 1.0);
    } else {
        gl_FragColor = vec4(1.0);
    }
}
