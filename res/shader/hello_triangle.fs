#version 330 core
in vec3 triangle_color;
out vec4 FragColor;
void main()
{
   FragColor = vec4(triangle_color,1.0);
};
