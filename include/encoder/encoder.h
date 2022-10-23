/// $COPYRIGHT

/// @file 3D Mesh encoder header goes here
///
/// @brief 3d mesh encoder class definition

#pragma once

#include <memory>
#include "options.h"

class Encoder {
public:
    Encoder();

    // Encodes mesh of a glTF file and returns a encoded Mesh.
    // Returns nullptr when encode fails.
    StatusOr<std::unique_ptr<Mesh>> EncodeMeshFromFile(
        std::string &fileName
    );

    // Write encoded mesh to a glTF file
    void WriteEncodedMeshToFile (
        Mesh *mesh,
        const std::string &fileName
    );

    // Returns the options instance used by the encoder that can be used by users
    // to control the decoding process.
    EncoderOptions *options (
    ) {
        return &mOptions;
    }

    FileOptions *fileOptions(
    ) {
        return &mFileOptions;
    }

private:
    EncoderOptions mOptions;
    FileOptions mFileOptions;

    tinygltf::Model mModel;
    tinygltf::TinyGLTF mLoader;
};
