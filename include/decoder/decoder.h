/// $COPYRIGHT

/// @file 3D Mesh decoder header goes here
///
/// @brief 3d mesh decoder class definition

#pragma once

#include <memory>
#include "options.h"

class Decoder {
public:
    Decoder();

    // Decodes a encoded mesh stored in glTF file and returns a decoded mesh.
    // Returns nullptr when decode fails.
    StatusOr<std::unique_ptr<Mesh>> DecodeMeshFromFile (
        const std::string &fileName
    );

    // Write decoded mesh to a glTF file
    void WriteDecodedMeshToFile (
        Mesh *mesh,
        const std::string &fileName
    );

    // Returns the options instance used by the decoder that can be used by users
    // to control the decoding process.
    DecoderOptions *options(
    ) { 
        return &mOptions;
    }

    FileOptions *fileOptions() {
        return &mFileOptions;
    }

private:
    DecoderOptions mOptions;
    FileOptions mFileOptions;

    tinygltf::Model mModel;
    tinygltf::TinyGLTF mLoader;
};
