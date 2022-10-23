/// $COPYRIGHT

/// @file 3D Mesh encoder implementation goes here
///
/// @brief Used for gltf file as input to 3d mesh encoder 
///        compress geometry

// Define these only in *one* .cpp file.
#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "tiny_gltf/tiny_gltf.h"
#include "core/core.h"
#include "encoder/encoder.h"

static std::string GetFilePathExtension (
    const std::string &FileName
) {
  if (FileName.find_last_of(".") != std::string::npos)
    return FileName.substr(FileName.find_last_of(".") + 1);
  return "";
}

Encoder::Encoder (
) {
}

StatusOr<std::unique_ptr<Mesh>> Encoder::EncodeMeshFromFile (
    std::string &fileName
) {
    std::string gltfFilename(fileName);
    std::string ext = GetFilePathExtension(gltfFilename);
    std::string err, warn;

    // Load GLTF file to Model
    bool ret = false;
    if (ext.compare("glb") == 0) {
        ret = mLoader.LoadBinaryFromFile(
            &mModel,
            &err,
            &warn,
            gltfFilename.c_str()
        );
    } else {
        ret = mLoader.LoadASCIIFromFile(
            &mModel,
            &err,
            &warn,
            gltfFilename.c_str()
        );
    }

    // Loop around to extract mesh
    std::unique_ptr<Mesh> meshGeometry;

    return meshGeometry;
}

void Encoder::WriteEncodedMeshToFile (
    Mesh *mesh,
    const std::string &fileName
) {
    mLoader.WriteGltfSceneToFile(
        &mModel,
        fileName,
        true, // embedImages
        true, // embedBuffers
        true, // pretty print
        false
    ); // write binary
}
