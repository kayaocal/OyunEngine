#ifndef OYUN_MESH_H__
#define OYUN_MESH_H__

#include <vector>
#include <map>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>


#ifdef OyunEngine_EXPORTS
#define OYUN_API __declspec(dllexport)
#else
#define OYUN_API __declspec(dllimport)
#endif

namespace Oyun
{
    #define MAX_BONE_INFLUENCE 4

    struct OYUN_API Vertex
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

    class OYUN_API Mesh
    {
    protected:

        unsigned int mVbo, mVao, mEbo;

        void SetupMesh();


    public:

        std::vector<Vertex>         vertices;
        std::vector<unsigned int>   indices;
        struct Material* material;

        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Material* mat);

        void Draw(float* view, float* proj, float* transform);

    };

    /// @brief a model is a container for mesh and it's child meshes
    class OYUN_API Model
    {
    public:
        std::vector<Mesh*> meshes;
        std::string path;

        Model(const char*);

        void Draw(float* view, float* proj, float* transform);

        void SetShader(struct Shader*);
    private:
        struct Material* mMaterial;
    };

    class OYUN_API ModelStore
    {
        std::map<uint32_t, Model*> mModelMap;
        
    public:
        ModelStore();

        Model* Load(const char* path, uint32_t hash);

        Model* GetModelByPath(const char* path);
        Model* GetModel(uint32_t hash);

        static ModelStore& Get();
        
        void ProcessNode(Model* mdl, aiNode* node, const aiScene* scene);
        Mesh* ProcessMesh(aiMesh* mesh, const aiScene* scene);
        Model* Load(const char* path, char* buffer, size_t size, uint32_t hash);
        void LoadMaterialTextures(Material* engineMat, aiMaterial* mat, aiTextureType type);
    };

}

#endif //OYUN_MESH_H__