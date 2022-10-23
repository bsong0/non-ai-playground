/// $COPYRIGHT

/// @file 3D Mesh geometry header goes here
///
/// @brief 3D Mesh geometry class definition

#pragma once

#include <vector>

class Mesh {
public:
    Mesh();
    std::vector<float> *vertices() { return &mVertices; }

private:
    std::vector<float> mVertices;
    std::vector<float> mUVs;
    std::vector<float> mNormals;
    std::vector<float> mIndices;
};
