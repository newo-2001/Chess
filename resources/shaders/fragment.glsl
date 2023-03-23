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

struct Highlight
{
    vec3 color;
    vec2 location;
};

uniform sampler2D tex;

uniform Material material;
uniform vec3 cameraPos;

uniform DirectionalLight directionalLight;

const int MAX_HIGHLIGHTS = 2;

uniform int highlightCount;
uniform Highlight highlights[MAX_HIGHLIGHTS];

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

vec4 CalcHighlightColor(Highlight highlight)
{
    vec4 edge = abs(vec4(FragPos.xz - highlight.location, FragPos.xz - highlight.location - vec2(1)));
    
    const float DISTANCE = 0.1;
    float factor = min(min(min(edge.x, edge.y), edge.z), edge.w);

    if (factor > DISTANCE || edge.x > 1 || edge.y > 1 || edge.z > 1 || edge.w > 1)
    {
        return vec4(0);
    }

    return vec4(highlight.color * (1 - factor / DISTANCE), 1.0);
}

vec4 CalcHighlightColors()
{
    vec4 total = vec4(0);
    
    for (int i = 0; i < highlightCount; i++)
    {
        total += CalcHighlightColor(highlights[i]);
    }
    
    return total;
}

void main()
{
    vec4 lightColor = CalcDirectionalLight();
    vec4 textureColor = texture(tex, TexCoord);
    vec4 highlightColor = CalcHighlightColors();

    color = vec4(material.color, 1.0) * textureColor * lightColor + highlightColor;
}
