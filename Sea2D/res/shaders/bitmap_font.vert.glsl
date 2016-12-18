#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

// Exclusively for sprite shader
uniform vec4 spriteRectUV;  // Width = z, Height = w

// For font glyphs scaling
uniform vec2 glyphScale;

// For font glyphs spacing
uniform float xDisplacement;

out vec2 uv;

void main()
{
    mat4 glyphScaleMatrix = mat4(vec4(glyphScale.x, 0.0f, 0.0f, 0.0f),
                                 vec4(0.0f, glyphScale.y, 0.0f, 0.0f),
                                 vec4(0.0f, 0.0f, 1.0f, 0.0f),
                                 vec4(0.0f, 0.0f, 0.0f, 1.0f));
    
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * glyphScaleMatrix * (vec4(position, 1.0f) + vec4(xDisplacement, 0.0f, 0.0f, 1.0f));
    
    // From: http://forum.devmaster.net/t/spritesheet-animation-in-opengl/24020/2
    // spriteUV = SpriteFrame.xy + (UV * SpriteFrame.zw);
    uv = spriteRectUV.xy + (texCoord * spriteRectUV.zw);
}