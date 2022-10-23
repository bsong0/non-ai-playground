/// $COPYRIGHT

/// @file 3D Mesh decoder options header goes here
///
/// @brief 3d mesh decoder options class definition

#pragma once

#include <map>
#include <string>

class EncoderOptions {
public:
    EncoderOptions() {}
    bool IsOptionSet(const std::string &name) const {
        return mOptions.count(name) > 0;
    }
private:
    std::map<std::string, std::string> mOptions;
};
