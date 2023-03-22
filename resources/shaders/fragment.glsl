#version 330

in vec3 FragPos;
in vec2 TexCoord;
in vec3 Normal;

out vec4 color;

struct Material
{
    float specularIntensity;
    float shininess;
    vec3 color;
};

struct Light
{
    vec3 color;
    float ambientIntensity;
    float diffuseIntensity;
};

struct DirectionalLight
{
    Light base;
    vec3 direction;
};

uniform sampler2D tex;

uniform Material material;
uniform vec3 cameraPos;

uniform DirectionalLight directionalLight;

vec4 CalcLightByDirection(Light light, vec3 direction)
{
    vec4 ambientColor = vec4(light.color, 1.0) * light.ambientIntensity;
    
    float diffuseFactor = max(0.0, dot(normalize(Normal), normalize(direction)));
    vec4 diffuseColor = vec4(light.color, 1.0) * light.diffuseIntensity * diffuseFactor;

    vec4 specularColor = vec4(0);

    if (diffuseFactor > 0.0)
    {
        vec3 fragToCamera = normalize(cameraPos - FragPos);
        vec3 reflectedRay = normalize(reflect(direction, normalize(Normal)));

        float specularFactor = dot(fragToCamera, reflectedRay);
        if (specularFactor > 0.0)
        {
            specularFactor = pow(specularFactor, material.shininess);
            specularColor = vec4(light.color * material.specularIntensity * specularFactor, 1.0);
        }
    }

    return ambientColor + diffuseColor + specularColor;
}

vec4 CalcDirectionalLight()
{
    return CalcLightByDirection(directionalLight.base, directionalLight.direction);
}

void main()
{
    vec4 lightColor = CalcDirectionalLight();
    vec4 textureColor = texture(tex, TexCoord);

    color = vec4(material.color, 1.0) * textureColor * lightColor;
}
