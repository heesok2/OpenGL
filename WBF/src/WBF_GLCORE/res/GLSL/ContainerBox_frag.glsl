#version 330 core

out vec4 FragColor;

in vec3 aFragPos;
in vec3 aFragNormal;
in vec2 aFragTexcel;

uniform vec3 aEyePos;
uniform vec3 aLightPos;
uniform vec3 aLightColor;

uniform sampler2D aContainerTex2D;

void main()
{
	float fAmbient = 0.3;
	vec3 aAmbientColor = fAmbient * aLightColor;

	vec3 aNormal = normalize(aFragNormal);
	vec3 aLightDir = normalize(aLightPos - aFragPos);
	float fDiffuse = max(dot(aNormal, aLightDir), 0.f);
	vec3 aDiffuse = fDiffuse * aLightColor;

	float fSpecRatio = 0.3f;
	vec3 aViewDir = normalize(aEyePos - aFragPos);
	vec3 aReflectDir = reflect(-aLightDir, aNormal);
	float fSpecular = pow(max(dot(aViewDir, aReflectDir), 0.f), 32);
	vec3 aSpecular = fSpecRatio * fSpecular * aLightColor;

	vec3 result = (aAmbientColor + aDiffuse + aSpecular) * texture(aContainerTex2D, aFragTexcel).rgb;
	FragColor = vec4(result, 1.f);
}