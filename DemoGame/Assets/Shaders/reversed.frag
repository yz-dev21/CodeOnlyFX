#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D image;
uniform vec3 spriteColor;
uniform bool useTex;

void main()
{
    if (useTex)
    {
        color = texture(image, TexCoords);
        color = vec4(1.0 - color.rgb, color.a);
        if (color.a == 0)
            discard;
    }
    else
        color = vec4(spriteColor, 1.0);
}  