#pragma once

#include "glm/glm.hpp"
#include <vector>

#define EngineExport   __declspec( dllexport )

namespace Oyun
{

    #define MAX_BONE_INFLUENCE 4

    struct EngineExport Vertex
    {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoords;
        glm::vec3 tangent;
        // bitangent
        glm::vec3 bitangent;
        //bone indexes which will influence this vertex
        int boneIDs[MAX_BONE_INFLUENCE];
        //weights from each bone
        float boneWeights[MAX_BONE_INFLUENCE];
    };

    class EngineExport Mesh
    {
    protected:

        unsigned int VBO, VAO, EBO;

        void SetupMesh();

    public:

        std::vector<Vertex>         vertices;
        std::vector<unsigned int>   indices;
        struct Material* material;
    public:

        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Material* mat);

        void Draw(class Shader& shader);

    };

}