#ifndef SYSTEM_TYPE_H_
#define SYSTEM_TYPE_H_

namespace GLOO {

enum class SystemType { Simple, Pendulum, Cloth };

inline std::string SystemTypeToString(SystemType type) {
    switch (type) {
        case SystemType::Simple:
            return "Simple";
        case SystemType::Pendulum:
            return "Pendulum";
        case SystemType::Cloth:
            return "Cloth";
        default:
            return "Unknown type";
    }
}

} // namespace GLOO

#endif