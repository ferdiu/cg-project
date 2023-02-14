/**
 * @author: MANZELLA Federico
 * @badge-number: 170612
 * @assignment: 5
 */

#version 460 core

#define LIGHT_DIRECTIONAL 0
#define LIGHT_POINT 1
#define LIGHT_SPOT 2

// UNIFORMS
uniform vec4 color;
uniform bool useTex;
uniform sampler2D tex;
uniform vec3 viewPos;

// ATTENUATION
struct Attenuation {
    float constant;
    float linear;
    float quadratic;
};

// LIGHT
struct Light {
    int type;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    vec3 direction;
    vec3 position;

    Attenuation attenuation;

    float cutOff;
    float outerCutOff;
};

// UNIFORMS LIGHTS
uniform Light light0;
uniform vec4 globAmb;

// MATERIAL
struct Material {
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;

    vec4 emission;

    float shininess;
};

// UNIFORMS MATERIAL
uniform Material material;

// PASSED FROM VERTEX
in vec3 fragcoord;
in vec2 texcoord;
in vec3 normalcoord;

// OUTPUT COLOR
out vec4 colorsOut;

// PRIVATES
vec4 tmpColor;

// FUNCTION HEADER
vec3 calcLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir);

// ----------------------------------------------------------------------

void main(void)
{
    tmpColor = globAmb * (useTex ? texture(tex, texcoord) : color);

    // properties
    vec3 norm = normalize(normalcoord);
    vec3 viewDir = normalize(viewPos - fragcoord);

    // TODO: add support for multiple lights
//     vec3 result = vec3(0);
//     for (int i = 0; i < NR_LIGHTS; i++)
//         result += calcLight(light0, norm, fragcoord, viewDir);

    colorsOut = tmpColor * vec4(calcLight(light0, norm, fragcoord, viewDir), tmpColor.a);
}

// ----------------------------------------------------------------------

// calculates the color when using a directional light.
vec3 calcDirLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(-light.direction);

    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);

    // blinn-phong
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);

    // combine results
    vec3 ambient = light.ambient * material.diffuse.xyz;
    vec3 diffuse = light.diffuse * diff * material.diffuse.xyz;
    vec3 specular = light.specular * spec * material.specular.xyz;

    return (ambient + diffuse + specular + material.emission.rgb);
}

// calculates the color when using a point light.
vec3 calcPointLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPos);

    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);

    // blinn-phong
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);

    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.attenuation.constant +
                               light.attenuation.linear * distance +
                               light.attenuation.quadratic * (distance * distance));

    // combine results
    vec3 ambient = light.ambient * material.diffuse.xyz;
    vec3 diffuse = light.diffuse * diff * material.diffuse.xyz;
    vec3 specular = light.specular * spec * material.specular.xyz;

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular + material.emission.rgb);
}

// calculates the color when using a spot light.
vec3 calcSpotLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPos);

    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);

    // blinn-phong
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);

    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.attenuation.constant +
                               light.attenuation.linear * distance +
                               light.attenuation.quadratic * (distance * distance));

    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    // combine results
    vec3 ambient = light.ambient * material.diffuse.xyz;
    vec3 diffuse = light.diffuse * diff * material.diffuse.xyz;
    vec3 specular = light.specular * spec * material.specular.xyz;

    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    return (ambient + diffuse + specular + material.emission.rgb);
}

vec3 calcLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    if (light0.type == LIGHT_SPOT)
        return calcSpotLight(light0, normal, fragPos, viewDir);
    else if (light0.type == LIGHT_POINT)
        return calcPointLight(light0, normal, fragPos, viewDir);
    else if (light0.type == LIGHT_DIRECTIONAL)
        return calcDirLight(light0, normal, fragPos, viewDir);
    else
        // classic magenta error
        return vec3(1.0, 0.0, 1.0);
}
