#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec3 FragPos;//声明顶点着色器的输出变量 FragPos，它是一个 vec3 类型的变量，用于将顶点的世界坐标位置传递给片段着色器
out vec3 Normal;//声明顶点着色器的输出变量 Normal，它是一个 vec3 类型的变量，用于将经过法线矩阵处理后的法向量传递给片段着色器
out vec2 TexCoords;//声明顶点着色器的输出变量 TexCoords，它是一个 vec2 类型的变量，用于将顶点的纹理坐标传递给片段着色器

uniform mat4 model; //声明一个 mat4 类型的uniform变量 model，用于传递模型矩阵。
uniform mat4 view; // 声明一个 mat4 类型的uniform变量 view，用于传递视图矩阵。
uniform mat4 projection;//声明一个 mat4 类型的uniform变量 projection，用于传递投影矩阵

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;//使用模型矩阵的逆转置矩阵，将顶点法向量变换为世界坐标系下的法向量，并赋值给输出变量 Normal。
    TexCoords = aTexCoords;

    gl_Position = projection * view * vec4(FragPos, 1.0);//计算顶点位置在视图和投影矩阵下的最终位置，并赋值给内置变量 gl_Position，该变量表示顶点的裁剪坐标位置
}