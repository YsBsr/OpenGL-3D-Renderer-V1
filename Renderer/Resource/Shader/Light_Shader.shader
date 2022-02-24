#shader vertex
#version 460 core

in vec4 position;
in vec4 color;
in vec2 texcoord;
in vec4 normal;

out vec4 Color;
out vec2 Texcoord;
out vec4 Normal;
out vec4 FragmentPosition;

uniform mat4 trans; //model;
uniform mat4 view;
uniform mat4 proj;


void main()
{
	Color = color;
	Texcoord = texcoord;
	gl_Position = proj * view * trans * position;
	FragmentPosition = trans * position;
	Normal = mat4(transpose(inverse(trans))) * normal;
}

#shader fragment
#version 460 core

in vec4 Color;
in vec2 Texcoord;
in vec4 Normal;
in vec4 FragmentPosition;
in vec4 previousFragmentPosition;

out vec4 outColor;

uniform sampler2D tex;

uniform vec4 lightingColor;
uniform vec4 objectColor;
uniform vec4 lightPosition;
uniform vec4 viewerPosition;

uniform float constant;
uniform float linear_;
uniform float quadratic;

uniform sampler2D texFramebuffer;

void main()
{
	float ambientStrength = 0.1f;
	vec4 ambient = ambientStrength * lightingColor;
	
	vec4 norm = normalize(Normal);
	vec4 lightDirection = normalize(lightPosition - FragmentPosition);

	/*float distance = length(lightPosition - FragmentPosition);
	float attenuation = 1.0f / (constant + linear_ * distance + quadratic * (distance * distance));*/

	float dot_product = dot(norm, lightDirection);

	//ambient *= attenuation;

	if (dot_product < 0) {
		outColor = ambient * objectColor;
		return;
	} 

	float diff = max(dot_product, 0.0f);
	vec4 diffuse = diff * lightingColor;

	float specularStrength = 0.5;

	vec4 viewerDirection = normalize(viewerPosition - FragmentPosition);
	//vec4 reflectionDirection = reflect(-lightDirection, norm);
	vec4 halfWayDirection = normalize(lightDirection + viewerDirection);

	//float spec = pow(max(dot(viewerDirection, reflectionDirection), 0.0f), 32);
	float spec = pow(max(dot(norm, halfWayDirection), 0.0f), 128);

	vec4 specular = specularStrength * spec * lightingColor;

	/*diffuse *= attenuation;
	specular *= attenuation;*/

	vec4 result = (ambient + diffuse + specular) * objectColor;

	outColor = result;
	//outColor = lightingColor * objectColor;
	//outColor = texture(tex, Texcoord); // texture(tex2, Texcoord);
	//outColor = vec4(1.0f, 0.2f, 0.3f, 1.0f);
	//outColor = texture(tex, Texcoord);
}