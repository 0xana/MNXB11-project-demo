#ifndef ANALYSIS_H
#define ANALYSIS_H
#include <TFile.h>
#include <TH1D.h>

#include <iostream>
#include <string>
#include <vector>

#include "Measurement.h"
// Create histograms of the signal and background measurements as well as a
// histogram representing the sum of the other two and store the results in a
// ROOT file with name given by output_filename
void signal_and_background(const std::vector<Measurement>& measurements,
                           const std::string& output_filename);
void some_analysis(const std::vector<Measurement>& measurements,
                   const std::string& output_filename);
void some_other_analysis(const std::vector<Measurement>& measurements,
                         const std::string& output_filename);
#endif /* ANALYSIS_H */
