#ifndef MODEL_H
#define MODEL_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh.h"

#include <learnopengl/shader_m.h>

#include <string>
#include <vector>

using namespace std;

class Model {
    public:
        vector<Mesh> meshes;
        string directory;
        
        Model(char *path) 
        {
            loadModel(path);
        }

        void Draw(Shader shader)
        {
            for (int i = 0; i < meshes.size(); i++)
            {
                meshes[i].Draw(shader);
            } 
        }

    private:
        void loadModel(string path)
        {
            Assimp::Importer Importer;
            const aiScene *scene = Importer.ReadFile(path, aiProcess_Triangulate|aiProcess_FlipUVs);
            if(!scene || scene->mFlags && AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
            {
                cout << "MODEL->loadModel failed!" << Importer.GetErrorString() << endl;
                return;
            }
            directory = path.substr(0, path.find_last_of("/"));
            processNode(scene->mRootNode, scene);
            
        }

        void processNode(aiNode *node, const aiScene *scene)
        {
            for (int i = 0; i < node->mNumMeshes; i++)
            {
                aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
                meshes.push_back(processMesh(mesh, scene));
            }

            for (int i = 0; i < node->mNumChildren; i++)
            {
                aiNode *n = node->mChildren[i];
                processNode(n, scene);
            }
            
        }

        Mesh processMesh(aiMesh *mesh, const aiScene *scene)
        {
            vector<Vertex> vertices;
            vector<unsigned int> indices;
            vector<Texture> textures;

            for(unsigned int i = 0; i < mesh->mNumVertices; i++)
            {
                Vertex vertex;
                // 处理顶点位置、法线和纹理坐标
                glm::vec3 vector;
                vector.x = mesh->mVertices[i].x;
                vector.y = mesh->mVertices[i].y;
                vector.z = mesh->mVertices[i].z;
                vertex.Position = vector;
                if(mesh->HasNormals())
                {
                    vector.x = mesh->mNormals[i].x;                
                    vector.y = mesh->mNormals[i].y;                
                    vector.z = mesh->mNormals[i].z;
                    vertex.Normal = vector;               
                }
                if(mesh->mTextureCoords[0])
                {
                    glm::vec2 coord;
                    coord.x = mesh->mTextureCoords[0][i].x;
                    coord.y = mesh->mTextureCoords[0][i].y;
                    vertex.TexCoords = coord;
                }
                else 
                {
                    vertex.TexCoords = glm::vec2(0.0f);
                }
            }
            // 处理索引

            
            // 处理材质
            if(mesh->mMaterialIndex >= 0)
            {
                
            }

            return Mesh(vertices, indices, textures);
        }
};


#endif