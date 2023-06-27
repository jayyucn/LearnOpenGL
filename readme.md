# 环境依赖
1. 安装mingw编译工具，并设置好环境变量。如果项目无法直接运行，如图![](docs\assets\glfw_error_01.png)，可能是glfw预编译的二进制版本不一定能满足自己电脑的运行环境,需要自行编译。按后续步骤操作（***正常情况下可以从4开始，如果不行的话再从2开始***）
2. 要编译glfw 先下载[CMake](https://cmake.org/download/)![](docs\assets\glfw_02.png)
3. 下载[glfw仓库](https://github.com/glfw/glfw.git)或者直接使用已下载好的项目 `dependency/glfw`
 ![](docs\assets\glfw_03.png)
 ![](docs\assets\glfw_04.png)
 ![](docs\assets\glfw_05.png)
 ![](docs\assets\glfw_06.png)
4. cmd前往glfwbuild目录，输入 `make`
5. 在glfwbuild/src找到 `glfw3.dll`和`libglfw3dll.a`并替换项目中对应的文件。
6. 现在你应该可以正常运行的

# 参考
[vscode OpenGL 环境搭建](https://blog.csdn.net/sarono/article/details/86564726)
