#version 330 core

out vec4 FragColor;

in vec3 aFragPos;
in vec3 aFragNormal;

uniform vec3 aEyePos;
uniform vec3 aLightPos;
uniform vec3 aModelColor;
uniform vec3 aLightColor;

void main()
{
	float fAmbient = 0.1;
	vec3 aAmbientColor = fAmbient * aLightColor;

	vec3 aNormal = normalize(aFragNormal);
	vec3 aLightDir = normalize(aLightPos - aFragPos);
	float fDiffuse = max(dot(aNormal, aLightDir), 0.f);
	vec3 aDiffuse = fDiffuse * aLightColor;

	float fSpecularRatio = 0.3f;
	vec3 aViewDir = normalize(aEyePos - aFragPos);
	vec3 aRefDir = reflect(-aLightDir, aNormal);
	float fSpecular = pow(max(dot(aViewDir, aRefDir), 0.f), 32);
	vec3 aSpecular = fSpecularRatio * fSpecular * aLightColor;

	vec3 result = (aAmbientColor + aDiffuse + aSpecular) * aModelColor;
	FragColor = vec4(result, 1.f);
}