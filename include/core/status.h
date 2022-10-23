/// $COPYRIGHT

/// @file Status header goes here
///
/// @brief Status class definition

#pragma once

#include <ostream>
#include <string>

// Class encapsulating a return status of an operation with an optional error
// message. Intended to be used as a return type for functions instead of bool.
class Status {
public:
    enum Code {
        OK = 0,
        ERROR = -1,                // Used for general errors.
        IO_ERROR = -2,             // Error when handling input or output stream.
        INVALID_PARAMETER = -3,    // Invalid parameter passed to a function.
    };

    Status() : mCode(OK) {}
    Status(const Status &status) = default;
    Status(Status &&status) = default;
    explicit Status(Code code) : mCode(code) {}
    Status(Code code, const std::string &errorMsg)
        : mCode(code), mErrorMsg(errorMsg) {}

    Code code() const { return mCode; }
    const std::string &errorMsgString() const { return mErrorMsg; }
    const char *errorMsg() const { return mErrorMsg.c_str(); }
    std::string codeString() const {
        switch (mCode) {
            case Code::OK:
                return "OK";
            case Code::ERROR:
                return "ERROR";
            case Code::IO_ERROR:
                return "IO_ERROR";
            case Code::INVALID_PARAMETER:
                return "INVALID_PARAMETER";
        }
    }
    std::string codeAndErrorString() const {
        return codeString() + ": " + errorMsgString();
    }

    bool operator==(Code code) const { return code == mCode; }
    bool ok() const { return mCode == OK; }

    Status &operator=(const Status &) = default;

    private:
        Code mCode;
        std::string mErrorMsg;
};

inline std::ostream &operator<<(std::ostream &os, const Status &status) {
    os << status.errorMsgString();
    return os;
}
inline Status OkStatus() { return Status(Status::OK); }
inline Status ErrorStatus(const std::string &msg) {
  return Status(Status::ERROR, msg);
}

// Evaluates an expression that returns Status. If the status is not OK,
// the macro returns the status object.
#define RETURN_IF_ERROR(expression)             \
  {                                             \
    const Status localStatus = (expression);    \
    if (!localStatus.ok()) {                    \
      return localStatus;                       \
    }                                           \
  }
