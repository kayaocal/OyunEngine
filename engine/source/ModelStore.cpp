#include <glad/glad.h>
#include <glm/glm.hpp>

#include "subsystems/ResourceSubsystem.h"
#include "subsystems/LogSubsystem.h"
#include "Material.h"
#include "Texture.h"
#include "Shader.h"
#include "FileIO.h"

#include "ModelStore.h"
#include <assimp/postprocess.h>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"

namespace Oyun
{
    Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Material* material)
    {
        this->vertices = vertices;
        this->indices = indices;
        this->material = material;
        SetupMesh();
    }
    
    void Mesh::SetupMesh()
    {
        glGenVertexArrays(1, &mVao);
        glGenBuffers(1, &mVbo);
        glGenBuffers(1, &mEbo);

        glBindVertexArray(mVao);
        glBindBuffer(GL_ARRAY_BUFFER, mVbo);

        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEbo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
            &indices[0], GL_STATIC_DRAW);

        // vertex positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
        // vertex normals
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
        // vertex texture coords
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

        // ids
        glEnableVertexAttribArray(5);
        glVertexAttribIPointer(5, 4, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, boneIDs));

        // weights
        glEnableVertexAttribArray(6);
        glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, boneWeights));

        glBindVertexArray(0);
    }


    void Mesh::Draw(float* view, float* proj, float* transform)
    {
        material->UseShader();
        material->ApplyTexturesToShader();
        material->ApplyShaderMatrix(view, proj, transform);
        // draw mesh
        glBindVertexArray(mVao);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // always good practice to set everything back to defaults once configured.
        glActiveTexture(GL_TEXTURE0);
    }

    Model::Model(const char* modelPath)
        : path(modelPath)
    {
    }

    void  Model::SetShader(Shader* shd)
    {
        
        for (auto m : meshes)
        {
            m->material->SetShader(shd);
        }
    }

    void  Model::Draw(float* view, float* proj, float* transform)
    {
      

        for(auto m : meshes)
        {
            m->Draw(view, proj, transform);
        }
    }

    ModelStore& ModelStore::Get()
    {
        static ModelStore store;
        return store;
    }

    void ModelStore::ProcessNode(Model* mdl, aiNode* node, const aiScene* scene)
    {
        // process all the node's meshes (if any)
        for (unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            mdl->meshes.push_back(ProcessMesh(mesh, scene));
        }
        // then do the same for each of its children
        for (unsigned int i = 0; i < node->mNumChildren; i++)
        {
            ProcessNode(mdl, node->mChildren[i], scene);
        }
    }

    Mesh* ModelStore::ProcessMesh(aiMesh* mesh, const aiScene* scene)
    {
        // data to fill
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;

        // walk through each of the mesh's vertices
        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            Vertex vertex;
            glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
            // positions
            vector.x = mesh->mVertices[i].x;
            vector.y = mesh->mVertices[i].y;
            vector.z = mesh->mVertices[i].z;
            vertex.position = vector;
            // normals
            if (mesh->HasNormals())
            {
                vector.x = mesh->mNormals[i].x;
                vector.y = mesh->mNormals[i].y;
                vector.z = mesh->mNormals[i].z;
                vertex.normal = vector;
            }
            // texture coordinates
            if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
            {
                glm::vec2 vec;
                // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
                // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
                vec.x = mesh->mTextureCoords[0][i].x;
                vec.y = mesh->mTextureCoords[0][i].y;
                vertex.texCoords = vec;

                // tangent
                if (mesh->mTangents)
                {
                    vector.x = mesh->mTangents[i].x;
                    vector.y = mesh->mTangents[i].y;
                    vector.z = mesh->mTangents[i].z;
                    vertex.tangent = vector;
                }

                // bitangent
                if (mesh->mBitangents)
                {
                    vector.x = mesh->mBitangents[i].x;
                    vector.y = mesh->mBitangents[i].y;
                    vector.z = mesh->mBitangents[i].z;
                    vertex.bitangent = vector;

                }
            }
            else
                vertex.texCoords = glm::vec2(0.0f, 0.0f);

            vertices.push_back(vertex);
        }
        // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            // retrieve all indices of the face and store them in the indices vector
            for (unsigned int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }
        // process materials
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
        // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
        // Same applies to other texture as the following list summarizes:
        // diffuse: texture_diffuseN
        // specular: texture_specularN
        // normal: texture_normalN

        Material* engineMat = new Material();

        // 1. diffuse maps
        LoadMaterialTextures(engineMat, material, aiTextureType_DIFFUSE);
        // 2. specular maps
        LoadMaterialTextures(engineMat, material, aiTextureType_SPECULAR);
        // 3. normal maps
        LoadMaterialTextures(engineMat, material, aiTextureType_HEIGHT);
        // 4. height maps
        LoadMaterialTextures(engineMat, material, aiTextureType_AMBIENT);

        // return a mesh object created from the extracted mesh data
        return new Mesh(vertices, indices, engineMat);
    }

    Model* ModelStore::Load(const char* path, char* buffer, size_t size, uint32_t hash)
    {

        Assimp::Importer import;
        const aiScene* scene = import.ReadFileFromMemory(buffer, size, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace, "OBJ");

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            LOG << "ERROR::ASSIMP::" << import.GetErrorString();
            return nullptr;
        }

        Model* mdl = new Model(path);
        ProcessNode(mdl, scene->mRootNode, scene);

        mModelMap.insert(std::pair<uint32_t, Model*>(hash, mdl));
        return mdl;
    }

    Model* ModelStore::Load(const char* path, uint32_t hash)
    {
        Assimp::Importer import;
        const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            LOG << "ERROR::ASSIMP::" << import.GetErrorString();
            return nullptr;
        }
        
        Model* mdl = new Model(path);
        ProcessNode(mdl, scene->mRootNode, scene);
        
        mModelMap.insert (std::pair<uint32_t, Model*>(hash, mdl));
        return mdl;
    }
       
    Model* ModelStore::GetModel(uint32_t hash)
    {
        auto mdl = mModelMap.find(hash);
        if (mdl != mModelMap.end())
        {
            return mdl->second;
        }

        return nullptr;
    }

    Model* ModelStore::GetModelByPath(const char* path)
    {
        uint32_t hash = GetHash(path);
        return GetModel(hash);
    }

    ModelStore::ModelStore()
    {

    }

    // checks all material textures of a given type and loads the textures if they're not loaded yet.
    // the required info is returned as a Texture struct.
    void ModelStore::LoadMaterialTextures(Material* engineMat, aiMaterial* mat, aiTextureType type)
    {
        if (engineMat == nullptr)
        {
            return;
        }

        for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
        {
            aiString str;
            mat->GetTexture(type, i, &str);
            // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
            Texture* loadedTexture = ResourceSubsystem::Get().LoadTexture(str.C_Str());
            if (loadedTexture == nullptr)
            {
                LOG << "Can not load texute at : " << str.C_Str();
                continue;
            }

            engineMat->textures.insert(std::pair<Texture*, MaterialTextureType>(loadedTexture, static_cast<MaterialTextureType>(type)));
        }
    }

}//namespace Oyun