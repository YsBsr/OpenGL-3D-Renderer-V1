#shader vertex
#version 460 core

in vec4 position;
in vec4 color;
in vec2 texcoord;
in vec2 texcoord2;

out vec4 Color;
out vec2 Texcoord;
out vec2 Texcoord2;

uniform mat4 trans; //model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
	Color = color;
	Texcoord = texcoord;
	Texcoord2 = texcoord2;
	gl_Position = proj * view * trans * position;
}

#shader fragment
#version 460 core

in vec4 Color;
in vec2 Texcoord;

out vec4 outColor;

uniform sampler2D tex;

void main()
{
	//outColor = Color;
	outColor = texture(tex, Texcoord);
	//outColor = vec4(1.0f, 0.2f, 0.3f, 1.0f);
}