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
  btw, the vertex's data is represented using vertex attributes that can contain any data we'd like(3D position, some color value etc.).

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
#### 多级渐远纹理 Mipmaps

> The origin of the term mipmap is an initialism of the Latin phrase ***multum in parvo***("much in a small space"), and map modeled on bitmap.--orgin from wikipedia

