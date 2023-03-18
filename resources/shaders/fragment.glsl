#version 330

in vec3 FragPos;
in vec2 TexCoord;
in vec3 Normal;

out vec4 color;

uniform sampler2D tex;

void main()
{
    vec4 lightColor = vec4(1.0);
    vec4 textureColor = texture(tex, TexCoord);

    vec4 color = textureColor * lightColor;
}
