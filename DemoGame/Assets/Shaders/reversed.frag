#version 330 core
in vec2 coTexCoords;
out vec4 coColor;

uniform sampler2D coImage;
uniform vec3 coSpriteColor;

void main()
{
    coColor = texture(coImage, coTexCoords);
    coColor = vec4(1.0 - coColor.rgb, coColor.a);
    if (coColor.a == 0)
        discard;
}  