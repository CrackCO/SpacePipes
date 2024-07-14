#include "PipeGenerator.hpp"

Mesh PipeGenerator::generateStraight(unsigned int quality, float radius) /* generates base straight pipe(X_ALIGNED) */
{
    //if (quality < 3) return 


    float angle = 0.0f, step = glm::pi<float>() * 2 / quality;

    std::vector<Vertex> vertices;
    for (int i = 0; i < quality * 2; i += 2) {
        vertices.push_back({glm::vec3(  PIPE_LENGTH / 2.0f,  sin(angle) * radius, cos(angle) * radius)});
        vertices.push_back({glm::vec3(-(PIPE_LENGTH / 2.0f), sin(angle) * radius, cos(angle) * radius)});

        angle += step;
    }

    std::vector<u32> indices(quality * 2 * 3);
    for (int i = 0; i < quality * 2; i+=2) { /* indexing for each surface */ 
        if (i + 2 != quality * 2) {
            /* index magic */
            indices.push_back(i);   /* first triangle */
            indices.push_back(i+1);
            indices.push_back(i+3);

            indices.push_back(i);   /* second triangle */
            indices.push_back(i+3);
            indices.push_back(i+2);

        } else {
            indices.push_back(i);
            indices.push_back(i+1);
            indices.push_back(1);

            indices.push_back(i);
            indices.push_back(1);
            indices.push_back(0);

        }
    }

    return Mesh(vertices, indices);
}

Mesh PipeGenerator::generateBent(u32 quality, float radius) /* generates base bent pipe(POS_X_TO_NEG_Y) */
{
    //if (quality < 3) return 
    //if (bentQuality < 3) return

    float step = glm::pi<float>() * 2 / quality;
    float angle = 0.0f;
    u32 bentQuality = 16;
    float bentStep = glm::pi<float>() / 2 / bentQuality;

    std::vector<Vertex> vertices;
    for (int i = 0; i <= bentQuality; ++i) {
        for (int j = 0; j < quality; ++j) {
            glm::mat4 rotationMat = glm::rotate(glm::mat4(1.0f), -bentStep * i, glm::vec3(0.0f, 0.0f, 1.0f));
            glm::vec3 vertex = glm::vec3(sin(glm::pi<float>() / 2 + angle) * radius - radius, 0.0f, cos(glm::pi<float>() / 2 + angle) * radius);
            vertices.push_back({glm::vec3(rotationMat * glm::vec4(vertex, 1.0f)) + glm::vec3(radius, -radius, 0.0f)});
            angle += step;
        }
        angle = 0.0f;
    }

    std::vector<u32> indices;
    for (int i = 0; i < bentQuality; ++i) {
        for (int j = 0; j < quality; ++j) {
            if (j == 0) {
                indices.push_back(quality * i);
                indices.push_back(quality * (i+1) + 1);
                indices.push_back(quality * i + 1);
            } else if (j == quality - 1) {
                indices.push_back(quality * i + j);
                indices.push_back(quality * (i+1) + j);
                indices.push_back(quality * (i+1));
            } else {
                indices.push_back(quality * i + j);
                indices.push_back(quality * (i+1) + j);
                indices.push_back(quality * (i+1) + j + 1);

                indices.push_back(quality * i + j);
                indices.push_back(quality * (i+1) + j + 1);
                indices.push_back(quality * i + j + 1);
            }                
        }
    }

    return Mesh(vertices, indices);
}

Mesh PipeGenerator::generateMesh(pipeType type)
{
    static Mesh straight;
    static Mesh bent;
    static bool initialized = false;

    if (!initialized) {
        straight = generateStraight(QUALITY, RADIUS);
        bent = generateBent(QUALITY, RADIUS);
        initialized = true;
    }

    switch (type) {
        case X_ALIGNED: case Y_ALIGNED: case Z_ALIGNED:
            return straight;

        default:
            return bent;
    }
}


glm::mat4 PipeGenerator::generateRotation(pipeType type)
{
    glm::mat4 rotation = glm::mat4(1.0f);

    switch (type) {
        /* rotation matrices from base straight(X_ALIGNED) */
        case X_ALIGNED: break; /* basic orientation */
        case Y_ALIGNED: rotation = glm::rotate(rotation, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f)); break;
        case Z_ALIGNED: rotation = glm::rotate(rotation, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f)); break;


        /* rotation matrices from base bent(POS_X_TO_NEG_Y) */
        case POS_X_TO_NEG_Y: break;/* basic orientation */
        case POS_X_TO_POS_Z: rotation = glm::rotate(rotation, glm::radians(90.0f),  glm::vec3(1.0f, 0.0f, 0.0f)); break;
        case POS_X_TO_POS_Y: rotation = glm::rotate(rotation, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f)); break;
        case POS_X_TO_NEG_Z: rotation = glm::rotate(rotation, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f)); break;

        case NEG_X_TO_NEG_Y: rotation =             glm::rotate(rotation, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f)); break;
        case NEG_X_TO_NEG_Z: rotation = glm::rotate(glm::rotate(rotation, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f)), glm::radians(90.0f),  glm::vec3(-1.0f, 0.0f, 0.0f)); break;
        case NEG_X_TO_POS_Y: rotation = glm::rotate(glm::rotate(rotation, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f)), glm::radians(180.0f), glm::vec3(-1.0f, 0.0f, 0.0f)); break;
        case NEG_X_TO_POS_Z: rotation = glm::rotate(glm::rotate(rotation, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f)), glm::radians(270.0f), glm::vec3(-1.0f, 0.0f, 0.0f)); break;

        case POS_Y_TO_POS_Z: rotation = glm::rotate(glm::rotate(rotation, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f)), glm::radians(90.0f),  glm::vec3(0.0f, 1.0f, 0.0f)); break;
        case POS_Y_TO_NEG_Z: rotation = glm::rotate(glm::rotate(rotation, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f)), glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f)); break;
        
        case NEG_Y_TO_POS_Z: rotation = glm::rotate(rotation, glm::radians(90.0f),  glm::vec3(0.0f, 1.0f, 0.0f)); break;
        case NEG_Y_TO_NEG_Z: rotation = glm::rotate(rotation, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f)); break;
        
    }

    return rotation;
}


Pipe PipeGenerator::generatePipe(pipeType type, glm::vec3 pos, glm::vec3 color)
{
    Mesh mesh = generateMesh(type);
    glm::mat4 transformation = glm::translate(glm::mat4(1.0f), pos) * generateRotation(type);

    return Pipe(type, mesh, transformation, color);
}
