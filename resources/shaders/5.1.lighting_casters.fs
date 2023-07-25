#version 330 core
out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light {
    vec3 position;//点光源
    // vec3 direction;//平行光源
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

//聚光
struct SpotLight {
    vec3 position;//光源位置
    vec3 direction;//聚光指向
    float cutoff;//切光角余弦值
    float outerCutoff;//外圈切光角余弦值

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 viewPos;
uniform Material material;
// uniform Light light;
uniform SpotLight light;

// void main()
// {
//     //衰减
//     float distance = length(light.position - FragPos);
//     float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
//     //ambient环境光
//     vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;

//     //diffuse漫反射
//     vec3 norm = normalize(Normal);
//     // vec3 lightDir = normalize(-light.direction);//平行光源
//     vec3 lightDir = normalize(light.position - FragPos);//点光源
//     float diff = max(dot(norm, lightDir), 0.0);
//     vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;

//     //specular 镜面光照
//     vec3 viewDir = normalize(viewPos - FragPos);
//     vec3 reflectDir = reflect(-lightDir, norm);
//     float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess * attenuation);
//     vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;

//     vec3 result = ambient + diffuse + specular;
//     FragColor = vec4(result * attenuation, 1.0);
// } 
void main()
{
    vec3 lightDir = normalize(light.position - FragPos);
    
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutoff - light.outerCutoff;
    float intensity = clamp((theta - light.outerCutoff)/epsilon, 0.0, 1.0);

    // ambient
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;
    // diffuse 
    vec3 norm = normalize(Normal);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb; 

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;  

    diffuse *= intensity;
    specular *= intensity;

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);

    // //比较的是余弦值，cutoff对应的切光角不会大于180度，根据余弦曲线可以发现theta时在聚光内
    // if(theta > light.cutoff)
    // {
    //     // ambient
    //     vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;
        
    //     // diffuse 
    //     vec3 norm = normalize(Normal);
    //     float diff = max(dot(norm, lightDir), 0.0);
    //     vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;  
        
    //     // specular
    //     vec3 viewDir = normalize(viewPos - FragPos);
    //     vec3 reflectDir = reflect(-lightDir, norm);  
    //     float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    //     vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;  
        
    //     // attenuation
    //     float distance    = length(light.position - FragPos);
    //     float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    

    //     // ambient  *= attenuation; // remove attenuation from ambient, as otherwise at large distances the light would be darker inside than outside the spotlight due the ambient term in the else branch
    //     diffuse   *= attenuation;
    //     specular *= attenuation;   
            
    //     vec3 result = ambient + diffuse + specular;
    //     FragColor = vec4(result, 1.0);
    // }
    // else 
    // {
    //     //聚光灯外使用环境光
    //     FragColor = vec4(light.ambient * vec3(texture(material.diffuse, TexCoords)), 1.0);
    // }
}