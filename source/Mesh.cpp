#include <glad/glad.h>
#include "Mesh.h"
#include "Material.h"
#include "Texture.h"
#include "Shader.h"


using namespace Engine;

void Mesh::SetupMesh()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(Vertex), &Vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(unsigned int),
        &Indices[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    glBindVertexArray(0);
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Material* material)
{
    Vertices = vertices;
    Indices = indices;
    this->material = material;
    SetupMesh();
}

void Mesh::Draw(Shader& shader)
{
    int counter[static_cast<int>(MaterialTextureType::MAX)] = {0};

    auto iterator = material->Textures.begin();
    int i = 0;
    while (iterator != material->Textures.end())
    {
        int textureType = static_cast<int>(iterator->second);
        std::string name{ Engine::TextureTypeNames[textureType] };
        name = name + std::to_string(counter[++textureType]);

        Engine::Texture* tex = iterator->first;

        glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding

        // now set the sampler to the correct texture unit
        glUniform1i(glGetUniformLocation(shader.ProgramId, name.c_str()), i);
        glBindTexture(GL_TEXTURE_2D, tex->Id);

        iterator++;
        i++;
    }
    
    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);


}
