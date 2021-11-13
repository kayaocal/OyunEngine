#pragma once

#include "glm/glm.hpp"
#include <vector>

#define EngineExport   __declspec( dllexport )

namespace Engine
{

    #define MAX_BONE_INFLUENCE 4

    struct EngineExport Vertex
    {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 TexCoords;
        glm::vec3 Tangent;
        // bitangent
        glm::vec3 Bitangent;
        //bone indexes which will influence this vertex
        int m_BoneIDs[MAX_BONE_INFLUENCE];
        //weights from each bone
        float m_Weights[MAX_BONE_INFLUENCE];
    };

    class EngineExport Mesh
    {
    protected:


        unsigned int VBO, VAO, EBO;

        void SetupMesh();

    public:

        std::vector<Vertex>         Vertices;
        std::vector<unsigned int>   Indices;
        struct Material* material;
    public:

        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Material* mat);

        void Draw(class Shader& shader);

    };

}