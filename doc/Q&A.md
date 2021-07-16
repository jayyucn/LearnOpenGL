需要系统性的学习，渲染知识

# Q&A:

* what is PCI-e?
* What is DRAM?
* 什么是饱和度?
* 深度测试和模板测试的作用
* alpha测试是在深度测试和模板测试之前吗？
* 什么是tessellation阶段
vertex storage

## OpenGL基本概念

* 什么是顶点(Vertex)
  A Vertex is a collection of  data per 3D coordinate.
  btw, the vertex's data is represented using vertex attributes that can contain any data we'd like(3D position, some color value and texture coordinates etc.).

* 什么是顶点数据(Vertex Data)

  A Vertex Data is a collection of vertices.
* 什么是图元(**primitive**)

  In order for OpenGL to know what to make of your collection of coordinates and color values OpenGL requires you to hint what kind of render types you want to form with the data. Do we want the data rendered as a collection of points, a collection of triangles or perhaps just one long line? Those hints are called primitives and are given to OpenGL while calling any of the drawing commands. Some of these hints are **GL_POINTS**, **GL_TRIANGLES** and **GL_LINE_STRIP**.

* 什么是片元(**framgment**)

  A fragment in OpenGL is all the data required for OpenGL to render a single pixel.

* 什么是透视除法(Perspective Division)

## Getting started
### 纹理 textures
#### 纹理座标 Texture Cordinate
Texture coordinates range from 0 to 1 in the x and y axis (remember that we use 2D texture images). Retrieving the texture color using texture coordinates is called sampling.Texture coordinates start at (0,0) for the **lower left corner** of a texture image to (1,1) for the upper right corner of a texture image.![tex_coords](D:\dev\LearnOpenGL\doc\assets\tex_coords.png)

#### 采样 Sampling
Retrieving the texture color using texture coordinates is calling Sampling.
#### 纹理环绕 texture wrapping
wrapping options offerred by OpenGL:
```c++
GL_REPEAT //the default behavior for textures. Repeat the texture image.
GL_MIRRORED_REPEAT // Same as GL_REPEAT but mirrors the image with each repeat.
GL_CLAMP_TO_EDGE // Clamps the corrdinates between 0 and 1. The result is that higher coordinates become clamped to the edge, resulting in a stretched edge pattern.
GL_CLAMP_TO_BORDER //Coordinates outside the range are now given a user-specified border color.
```
#### 纹理过滤 texture filtering
There are several options available, but what the most important are `GL_NEAREST` and `GL_LINEAR`.
> 延伸：线性插值和双/三线性插值 https://zhuanlan.zhihu.com/p/77496615
#### 多级渐远纹理 Mipmaps

> The origin of the term mipmap is an initialism of the Latin phrase ***multum in parvo***("much in a small space"), and map modeled on bitmap.--orgin from wikipedia

#纹理单元 Texture Unit
we can actually assign a location value to the texture sampler so we can set multiple textures at once in a fragment shader. This location of a texture is more commonly known as a texture unit.

### 变换 Transformations

#### 向量相乘 Vector-vector multiplication

##### 点乘 dot product

##### 叉乘 cross product

> Finding the direction of the cross product by the [right-hand rule](https://en.wikipedia.org/wiki/Right-hand_rule).

![220px-Right_hand_rule_cross_product.svg](D:\dev\LearnOpenGL\doc\assets\220px-Right_hand_rule_cross_product.svg.png)

####  行列式

n阶行列式：
$$\sum(-1)^t.a_{1p_1}.a_{2p_2}.a_{3p_3}$$
> t为$$p_1 p_2p_3$$的总逆序数
------

