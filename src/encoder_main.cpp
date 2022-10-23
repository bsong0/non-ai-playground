/// $COPYRIGHT

/// @file Template for 3D Mesh encoder
///
/// @brief Used for testing gltf as input to encoder and 
///        generating another gltf with compressed geometry

#include "app.h"

void Usage (
) {
    printf("Usage: encoder [options] -i input -o output\n\n");
    printf("Main options:\n");
    printf("  -h | -?         show help.\n");
    printf("  -i <input>      input file name.\n");
    printf("  -o <output>     output file name.\n");
}

int main (
    int argc,
    char **argv
) {
    Encoder encoder;

    const int argcCheck = argc - 1;
    for (int i = 1; i < argc; ++i) {
        if (!strcmp("-h", argv[i]) || !strcmp("-?", argv[i])) {
            Usage();
            return 0;
        } else if (!strcmp("-i", argv[i]) && i < argcCheck) {
            encoder.fileOptions()->mInputFileName = argv[++i];
        } else if (!strcmp("-o", argv[i]) && i < argcCheck) {
            encoder.fileOptions()->mOutputFileName = argv[++i];
        } 
    }

    if (argc < 3 || encoder.fileOptions()->mInputFileName.empty() ||
        encoder.fileOptions()->mOutputFileName.empty()) {
        Usage();
        return -1;
    }

    auto maybeMesh = encoder.EncodeMeshFromFile(
        encoder.fileOptions()->mInputFileName);
    if (!maybeMesh.ok()) {
        printf("Failed\t%s\t%s\n", encoder.fileOptions()->mInputFileName.c_str(),
            maybeMesh.status().errorMsg());
        return -1;
    }

    Mesh *mesh = maybeMesh.value().get();

    encoder.WriteEncodedMeshToFile(
        mesh,
        encoder.fileOptions()->mOutputFileName
    );

    return 0;
}