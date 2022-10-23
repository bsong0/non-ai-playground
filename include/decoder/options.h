/// $COPYRIGHT

/// @file 3D Mesh decoder options header goes here
///
/// @brief 3d mesh decoder options class definition

#pragma once

#include <map>
#include <string>

class DecoderOptions {
public:
    DecoderOptions() {}
    bool IsOptionSet(const std::string &name) const {
        return mOptions.count(name) > 0;
    }
private:
    std::map<std::string, std::string> mOptions;
};
