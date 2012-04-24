attribute vec3 vertexPosition;
attribute vec2 vertexTexCoord;
//attribute vec3 vertexNormal;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

varying vec2 texCoordOutput;

void main(void)
{
    texCoordOutput = vertexTexCoord;

    gl_Position = projectionMatrix * viewMatrix * vec4(vertexPosition, 1);
}
