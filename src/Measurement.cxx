#include "Measurement.h"
Measurement::Measurement(double signal, double background, int id)
    : signal{signal}, background{background}, id{id} {
  // You could do validation here if you want to make sure that you can't
  // even create an invalid measurement object!
  //
  // Alternatively, you can do the checks in a function like "is_valid" and
  // only persist valid measurements.

  // Check that neither signal nor background are infinite
  if (std::isinf(signal) || std::isinf(background)) {
    throw std::invalid_argument("Infinite measurement found!");
  }
  // Check that neither signal nor background is NaN (not a number)
  if (std::isnan(signal) || std::isnan(background)) {
    throw std::invalid_argument("Infinite measurement found!");
  }
  // Let's say that a valid measurement can't have a negative id, signal, or
  // background (use what suits your actual data!)
  if (id < 0) {
    throw std::invalid_argument(
        "A measurement cannot have a negative ID but was " +
        std::to_string(id));
  }
  if (signal < 0 || background < 0) {
    throw std::invalid_argument(
        "A signal or background value cannot be negative, but got signal " +
        std::to_string(signal) + " and background " +
        std::to_string(background));
  };
}
