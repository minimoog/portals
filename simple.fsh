uniform sampler2D texture;

varying highp vec2 texCoordOutput;

void main(void)
{
    gl_FragColor = texture2D(texture, texCoordOutput);
}
