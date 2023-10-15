#ifndef MEASUREMENT_H
#define MEASUREMENT_H
#include <cmath>
#include <stdexcept>
class Measurement {
 public:
  // Note: Bad idea, using two adjacent parameters that can be switched
  // accidentally!
  Measurement(double signal, double background, int id);

  // Alternative if you don't want to throw an exception for an invalid object
  bool is_valid() const { return (id > 0 && signal >= 0 && background >= 0); }
  int get_id() const { return id; }
  double get_background() const { return background; }
  double get_signal() const { return signal; }

 private:
  double signal;
  double background;
  int id;
};

#endif /* MEASUREMENT_H */
