#pragma once
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Oyun
{

    class Model
    {
    public:
        Model(char* path);
        void Draw(class Shader& shader);
    private:
        // model data
        std::vector<class Mesh*> meshes;
        std::string directory;

        void loadModel(std::string path);
        void processNode(aiNode* node, const aiScene* scene);
        class Mesh* processMesh(aiMesh* mesh, const aiScene* scene);
        void loadMaterialTextures(struct Material* engineMat, aiMaterial* mat, aiTextureType type);
    };
}


