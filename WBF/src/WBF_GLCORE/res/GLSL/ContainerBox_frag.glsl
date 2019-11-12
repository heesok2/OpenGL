#version 330 core

struct TLight
{
	vec3 aLightPos;
	vec3 aAmbient;
	vec3 aDiffuse;
	vec3 aSpecular;
};

struct TMaterial
{
	vec3 aAmbient; // The value must be 'vec3(1.f)'
	vec3 aDiffuse; // The value must be 'vec3(1.f)'
	vec3 aSpecular; // The value must be 'vec3(1.f)'
	float fShininess;

	sampler2D DiffuseTex2D;
	sampler2D SpecularTex2D;
};

out vec4 FragColor;

in vec3 aFragPos;
in vec3 aFragNormal;
in vec2 aFragTexcel;

uniform TLight tLight;
uniform TMaterial tMaterial;

void main()
{
	vec3 aAmbientColor = tLight.aAmbient * tMaterial.aAmbient * texture(tMaterial.DiffuseTex2D, aFragTexcel).rgb;

	vec3 aNormal = normalize(aFragNormal);
	vec3 aLightDir = normalize(tLight.aLightPos - aFragPos);
	float fDiffuse = max(dot(aNormal, aLightDir), 0.f);
	vec3 aDiffuseColor = tLight.aDiffuse * fDiffuse * tMaterial.aDiffuse * texture(tMaterial.DiffuseTex2D, aFragTexcel).rgb;

	vec3 aViewDir = normalize(-aFragPos);
	vec3 aReflectDir = reflect(-aLightDir, aNormal);
	float fSpecular = pow(max(dot(aViewDir, aReflectDir), 0.f), tMaterial.fShininess);
	vec3 aSpecularColor = tLight.aSpecular * fSpecular * tMaterial.aSpecular * texture(tMaterial.SpecularTex2D, aFragTexcel).rgb;

	vec3 result = aAmbientColor + aDiffuseColor + aSpecularColor;
	FragColor = vec4(result, 1.f);
}