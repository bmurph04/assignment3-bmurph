#ifndef INTEGRATOR_TYPE_H_
#define INTEGRATOR_TYPE_H_

namespace GLOO {
enum class IntegratorType { Euler, Trapezoidal, RK4 };

inline std::string IntegratorTypeToString(IntegratorType type) {
    switch (type) {
        case IntegratorType::Euler:
            return "Euler";
        case IntegratorType::Trapezoidal:
            return "Trapezoidal";
        case IntegratorType::RK4:
            return "RK4";
        default:
            return "Unknown type";
    }
}

} // namespace GLOO

#endif
