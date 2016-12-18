#version 330 core

in vec2 uv;

out vec4 fragColor;

uniform sampler2D ourTexture;
uniform vec4 tintColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);

void main()
{
    vec4 texelColor = tintColor * texture(ourTexture, uv);
    
    if(texelColor.a < 0.1f)
    {
        discard;
    }
    
    fragColor = texelColor;
}