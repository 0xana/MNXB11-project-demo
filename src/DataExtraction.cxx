#include "DataExtraction.h"

std::vector<Measurement> read_measurements(const std::string& filename) {
  // This code is WRONG! Can you spot the problems? It isn't easy, which is why
  // one of the reasons you don't want to write this kind of code yourself.
  std::ifstream file{filename};
  std::vector<Measurement> measurements;
  // Declaring a bunch of variables in advance, not good practice! Use a library
  // for reading CSV!
  int year, month, day, hour, minute, second, id;
  double signal, background, value;
  std::string header;
  // Assume first line is a header, read it first before we get the actual data
  std::getline(file, header);

  char comma;

  while (file >> year >> comma >> month >> comma >> day >> comma >> hour >>
         comma >> minute >> comma >> second >> comma >> id >> comma >> signal >>
         comma >> background >> comma >> value) {
    Measurement measurement{signal, background, id};
    if (measurement.is_valid()) {
      measurements.push_back(measurement);
    } else {
      std::cerr << "Warning: Skipping invalid measurement from (signal, "
                   "background, id): ("
                << signal << ", " << background << ", " << id << ")"
                << std::endl;
    }
  }
  return measurements;
}
