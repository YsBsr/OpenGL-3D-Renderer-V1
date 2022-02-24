#shader vertex
#version 460 core

in vec4 position;
in vec2 texcoord;

out vec2 Texcoord;

void main()
{
    gl_Position = position;
    Texcoord = texcoord;
} 

#shader fragment
#version 460 core

out vec4 outColor;

in vec2 Texcoord;

uniform sampler2D screenTexture;

void main()
{
    outColor = texture(screenTexture, Texcoord);
}