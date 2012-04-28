#version 130

in vec3 vertexPosition;
in vec2 vertexTexCoord;
in vec3 vertexNormal;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec2 texCoordOutput;
out vec3 normal;

void main(void)
{
    texCoordOutput = vertexTexCoord;
    normal = vertexNormal;

    gl_Position = projectionMatrix * viewMatrix * vec4(vertexPosition, 1);
}
