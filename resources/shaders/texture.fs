#version 330 core
out vec4 FragColor;

uniform sampler2D ourTexture;

in vec3 vertexColor; // 从顶点着色器传来的输入变量（名称相同、类型相同）
in vec2 TexCoord;//从顶点着色器传来的纹理坐标

void main()
{
    FragColor = texture(ourTexture, TexCoord);
}