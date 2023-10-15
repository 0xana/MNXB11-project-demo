#ifndef DATAEXTRACTION_H
#define DATAEXTRACTION_H
#include <TFile.h>
#include <TTree.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Measurement.h"

// Read measurement objects from a CSV file with name given by csv_filename
// parameter. Invalid measurements are ignored but give a warning.
std::vector<Measurement> read_measurements(const std::string& csv_filename);

#endif /* DATAEXTRACTION_H */
