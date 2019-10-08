#version 330 core

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;

uniform vec3 ourCameraPos;
uniform vec3 ourLightPos;
uniform vec3 ourModelColor;
uniform vec3 ourLightColor;

void main()
{
	float fAmbient = 0.1;
	vec3 aAmbientColor = fAmbient * ourLightColor;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(ourLightPos-FragPos);
	float diff = max(dot(norm, lightDir), 0.f);
	vec3 aDiffuse = diff * ourLightColor;

	float specular = 0.3f;
	vec3 viewDir = normalize(ourCameraPos - FragPos);
	vec3 refDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, refDir), 0.f), 32);
	vec3 aSpecular = specular * spec * ourLightColor;

	vec3 result = (aAmbientColor + aDiffuse + aSpecular) * ourModelColor;
	FragColor = vec4(result, 1.f);
}