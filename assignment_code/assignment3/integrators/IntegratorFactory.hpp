#ifndef INTEGRATOR_FACTORY_H_
#define INTEGRATOR_FACTORY_H_

#include "integrators/IntegratorBase.hpp"
#include "integrators/ForwardEulerIntegrator.hpp"
#include "integrators/TrapezoidalIntegrator.hpp"
#include "integrators/RK4Integrator.hpp"

#include <stdexcept>

#include "gloo/utils.hpp"

#include "integrators/IntegratorType.hpp"

namespace GLOO {
class IntegratorFactory {
 public:
  template <class TSystem, class TState>
  static std::unique_ptr<IntegratorBase<TSystem, TState>> CreateIntegrator(
      IntegratorType type) {
    if (type == IntegratorType::Euler) {
      return make_unique<ForwardEulerIntegrator<TSystem, TState>>();
    }
    if (type == IntegratorType::Trapezoidal) {
      return make_unique<TrapezoidalIntegrator<TSystem, TState>>();
    }
    if (type == IntegratorType::RK4) {
      return make_unique<RK4Integrator<TSystem, TState>>();
    }
    throw std::runtime_error("IntegratorType \"" + std::string(IntegratorTypeToString(type)) + "\" is not supported");
  }
};
}  // namespace GLOO

#endif
