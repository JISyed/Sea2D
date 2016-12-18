#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

// Exclusively for sprite shader
uniform vec4 spriteRectUV;  // Width = z, Height = w

out vec2 uv;

void main()
{
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0f);
    
    // From: http://forum.devmaster.net/t/spritesheet-animation-in-opengl/24020/2
    // spriteUV = SpriteFrame.xy + (UV * SpriteFrame.zw);
    uv = spriteRectUV.xy + (texCoord * spriteRectUV.zw);
}