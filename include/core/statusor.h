/// $COPYRIGHT

/// @file StatusOr header goes here
///
/// @brief StatusOr class definition

#pragma once

#include <ostream>
#include <string>

template <class T>
class StatusOr {
public:
    StatusOr() {}
    StatusOr(const StatusOr &) = default;
    StatusOr(StatusOr &&) = default;
    StatusOr(const Status &status) : mStatus(status) {}
    StatusOr(const T &value) : mStatus(OkStatus()), mValue(value) {}
    StatusOr(T &&value) : mStatus(OkStatus()), mValue(std::move(value)) {}
    StatusOr(const Status &status, const T &value)
        : mStatus(status), mValue(value) {}

    const Status &status() const { return mStatus; }
    const T &value() const & { return mValue; }
    const T &&value() const && { return std::move(mValue); }
    T &&value() && { return std::move(mValue); }

    const T &ValueOrDie() const & { return value(); }
    T &&ValueOrDie() && { return std::move(value()); }

    bool ok() const { return mStatus.ok(); }

private:
    Status mStatus;
    T mValue;
};