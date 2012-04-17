attribute highp vec3 vertexPosition;
attribute highp vec2 vertexTexCoord;
attribute highp vec3 vertexNormal;

uniform highp mat4 viewMatrix;
uniform highp mat4 projectionMatrix;

varying highp vec2 texCoordOutput;

void main(void)
{
    texCoordOutput = vertexTexCoord;

    gl_Position = projectionMatrix * viewMatrix * vec4(vertexPosition, 1);
}
