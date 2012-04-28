#version 130

uniform sampler2D texture;

in vec2 texCoordOutput;
in vec3 normal;

void main(void)
{
    gl_FragColor = texture2D(texture, texCoordOutput);
}
