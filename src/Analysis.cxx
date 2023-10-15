#include "Analysis.h"

void signal_and_background(const std::vector<Measurement>& measurements,
                           const std::string& output_filename) {
  // Note: We need .c_str() because TFile expects a C-string (i.e. a char*)
  // but output_filename is a std::string
  TFile output_file{output_filename.c_str(), "RECREATE"};
  TH1D* signal_histogram{new TH1D{"signal_histogram", "Signal", 100, 0, 3}};
  TH1D* background_histogram{
      new TH1D{"background_histogram", "Background", 100, 0, 3}};
  TH1D* sum_histogram{
      new TH1D{"signal_and_background", "Signal + Background", 100, 0, 3}};
  for (const auto measurement : measurements) {
    signal_histogram->Fill(measurement.get_signal());
    background_histogram->Fill(measurement.get_background());
  }
  // Add the contents of the bins in the sum and background histograms into the
  // (currently empty) sum histogram.
  sum_histogram->Add(background_histogram);
  sum_histogram->Add(signal_histogram);

  // Write the histograms to the output ROOT file
  signal_histogram->Write();
  background_histogram->Write();
  sum_histogram->Write();
}
// Note: We aren't giving a name to the parameter here, this tells the compiler
// that we know the parameters aren't used
void some_analysis(const std::vector<Measurement>& /*measurements*/,
                   const std::string& /*output_filename*/) {
  std::cout << "Here we could implement the code for a second analysis!"
            << std::endl;
  std::cout << "You could consider using a different translation unit for this "
               "to make it easier to work on the different analyzes "
               "independently in git!"
            << std::endl;
}
void some_other_analysis(const std::vector<Measurement>& /*measurements*/,
                         const std::string& /*output_filename*/) {
  std::cout << "Here we could implement the code for a third analysis!"
            << std::endl;
  std::cout << "You could consider using a different translation unit for this "
               "to make it easier to work on the different analyzes "
               "independently in git!"
            << std::endl;
}
