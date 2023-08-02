#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>

#include <learnopengl/shader_m.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <vector>

using namespace std;

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture {
    unsigned int id;
    string type;
};

class Mesh {
    public:
        /** 网格顶点数据*/
        vector<Vertex> vertices;
        /** 顶点索引*/
        vector<unsigned int> indices;
        /** 纹理*/
        vector<Texture> textures;
        Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures){
            this->vertices = vertices;
            this->indices = indices;
            this->textures = textures;
            setupMesh();
        }
        void Draw(Shader shader) {
            unsigned int diffuseNr = 1;
            unsigned int specularNr = 1;
            for(unsigned int i = 0; i < textures.size(); i++)
            {
                glActiveTexture(GL_TEXTURE0 + i);
                string number;
                string name = textures[i].type;
                if(name == "texture_diffuse")
                {
                    number = to_string(diffuseNr++);
                }
                else if (name == "texture_specular")
                {
                    number = to_string(specularNr++);
                }
                shader.setInt(("material."+ name + number).c_str(), i);
                glBindTexture(GL_TEXTURE_2D, textures[i].id);
            }
            glActiveTexture(GL_TEXTURE0);
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }
    private:
        /** 渲染数据*/ 
        unsigned int VAO, VBO, EBO;
        void setupMesh(){
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glGenBuffers(1, &EBO);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

            glBindVertexArray(VAO);
            //坐标
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
            /** 法线*/
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,     sizeof(Vertex), (void*)offsetof(Vertex, Normal));
            /** uv坐标*/
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
            glBindVertexArray(0);

        }
};

#endif