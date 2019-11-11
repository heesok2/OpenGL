#version 330 core

struct TLight
{
	vec3 aLightPos;
	vec3 aLightColor;
};

out vec4 FragColor;

in vec3 aFragPos;
in vec3 aFragNormal;
in vec2 aFragTexcel;

uniform TLight tLight;

uniform sampler2D aContainerTex2D;

void main()
{
	float fAmbient = 0.3;
	vec3 aAmbientColor = fAmbient * tLight.aLightColor;

	vec3 aNormal = normalize(aFragNormal);
	vec3 aLightDir = normalize(tLight.aLightPos - aFragPos);
	float fDiffuse = max(dot(aNormal, aLightDir), 0.f);
	vec3 aDiffuse = fDiffuse * tLight.aLightColor;

	float fSpecRatio = 0.3f;
	vec3 aViewDir = normalize(-aFragPos);
	vec3 aReflectDir = reflect(-aLightDir, aNormal);
	float fSpecular = pow(max(dot(aViewDir, aReflectDir), 0.f), 32);
	vec3 aSpecular = fSpecRatio * fSpecular * tLight.aLightColor;

	vec3 result = (aAmbientColor + aDiffuse + aSpecular) * texture(aContainerTex2D, aFragTexcel).rgb;
	FragColor = vec4(result, 1.f);
}