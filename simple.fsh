uniform sampler2D texture;

varying vec2 texCoordOutput;

void main(void)
{
    gl_FragColor = texture2D(texture, texCoordOutput);
}
