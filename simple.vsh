in vec3 vertexPosition;
in vec2 vertexTexCoord;
//attribute vec3 vertexNormal;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec2 texCoordOutput;

void main(void)
{
    texCoordOutput = vertexTexCoord;

    gl_Position = projectionMatrix * viewMatrix * vec4(vertexPosition, 1);
}
