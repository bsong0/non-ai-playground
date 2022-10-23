/// $COPYRIGHT

/// @file 3D Mesh decoder implementation goes here
///
/// @brief Used for gltf file as input to 3d mesh decoder 
///        generate a geometry

// Define these only in *one* .cpp file.
#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "tiny_gltf/tiny_gltf.h"
#include "core/core.h"
#include "decoder/decoder.h"

static std::string GetFilePathExtension(const std::string &FileName) {
  if (FileName.find_last_of(".") != std::string::npos)
    return FileName.substr(FileName.find_last_of(".") + 1);
  return "";
}

Decoder::Decoder (
){
}

StatusOr<std::unique_ptr<Mesh>> Decoder::DecodeMeshFromFile (
    const std::string &fileName) {
    std::string gltfFilename(fileName);
    std::string ext = GetFilePathExtension(gltfFilename);
    std::string err, warn;

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

    std::unique_ptr<Mesh> meshGeometry;

    return meshGeometry;
}

void Decoder::WriteDecodedMeshToFile (
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