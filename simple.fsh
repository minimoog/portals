uniform sampler2D texture;

in vec2 texCoordOutput;

void main(void)
{
    gl_FragColor = texture2D(texture, texCoordOutput);
}
