/// $COPYRIGHT

/// @file Template for 3D Mesh decoder
///
/// @brief Used for testing gltf as input to decoder and 
///        generating another gltf

#include "app.h"

void Usage (
) {
    printf("Usage: decoder [options] -i input -o output\n\n");
    printf("Main options:\n");
    printf("  -h | -?         show help.\n");
    printf("  -i <input>      input file name.\n");
    printf("  -o <output>     output file name.\n");
}

int main(
    int argc,
    char **argv
) {
    Decoder decoder;

    const int argcCheck = argc - 1;
    for (int i = 1; i < argc; ++i) {
        if (!strcmp("-h", argv[i]) || !strcmp("-?", argv[i])) {
            Usage();
            return 0;
        } else if (!strcmp("-i", argv[i]) && i < argcCheck) {
            decoder.fileOptions()->mInputFileName = argv[++i];
        } else if (!strcmp("-o", argv[i]) && i < argcCheck) {
            decoder.fileOptions()->mOutputFileName = argv[++i];
        } 
    }

    if (argc < 3 || decoder.fileOptions()->mInputFileName.empty() ||
        decoder.fileOptions()->mOutputFileName.empty()) {
        Usage();
        return -1;
    }

    auto maybeMesh = decoder.DecodeMeshFromFile(
        decoder.fileOptions()->mInputFileName);
    if (!maybeMesh.ok()) {
        printf("Failed\t%s\t%s\n", decoder.fileOptions()->mInputFileName.c_str(),
            maybeMesh.status().errorMsg());
        return -1;
    }

    Mesh *mesh = maybeMesh.value().get();

    decoder.WriteDecodedMeshToFile (
        mesh,
        decoder.fileOptions()->mOutputFileName
    );

    return 0;
}