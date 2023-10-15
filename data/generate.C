#include <TF1.h>
#include <TROOT.h>

#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>

// Signal on background from the first ROOT lecture
Double_t background_function(Double_t* x_ptr, Double_t* par) {
  auto x{x_ptr[0]};
  return par[0] + par[1] * x + par[2] * x * x;
}

// Lorenzian Peak function
Double_t lorentzian_peak_function(Double_t* x_ptr, Double_t* par) {
  auto x{x_ptr[0]};
  auto width{par[1]};
  auto peak{par[2]};
  return (0.5 * par[0] * width / TMath::Pi()) /
         TMath::Max(1.e-10, (x - peak) * (x - peak) + .25 * width * width);
}
void generate(std::string file_name, Int_t num_points) {
  std::ofstream output_file;
  output_file.open(file_name);

  TF1 signal{"signal", lorentzian_peak_function, 0, 3, 3};
  TF1 background{"background", background_function, 0, 3, 3};

  // Parameters from the ROOT fitting demo
  // p0, p1, p2 -> Background
  // p3, p4, p5 -> Signal
  //  1  p0          -8.64713e-01   8.91794e-01
  //  2  p1           4.58434e+01   2.64221e+00
  //  3  p2          -1.33214e+01   9.76963e-01
  //  4  p3           1.38074e+01   2.17751e+00
  //  5  p4           1.72309e-01   3.58302e-02
  //  6  p5           9.87281e-01   1.12690e-02

  signal.SetParameters(1.38074e+01, 1.72309e-01, 9.87281e-01);
  background.SetParameters(-8.64713e-01, 4.58434e+01, -1.33214e+01);
  // Write a header for the CSV file
  output_file << "year,month,day,hour,minute,second,id,background,signal,energy"
              << std::endl;
  for (int i = 0; i < num_points; i++) {
    const int id = i;
    const auto now = std::chrono::system_clock::now();
    // C-nonsense that deals with dates, better to use a library like date by
    // Howard hinnant!
    const auto time = std::chrono::system_clock::to_time_t(now);
    // Use standard localtime function to extract timestamp components
    const auto localTime = *std::localtime(&time);
    // Extract timestamp components
    const int year = localTime.tm_year + 1900;
    const int month = localTime.tm_mon + 1;
    const int day = localTime.tm_mday;
    const int hour = localTime.tm_hour;
    const int minute = localTime.tm_min;
    const int second = localTime.tm_sec;
    // Generate random numbers from the combined function
    const double background_value{background.GetRandom()};
    const double signal_value{signal.GetRandom()};

    double energy = signal_value + background_value;
    // Delay with 1 millisecond, to get some difference between the
    // timestamps!
    std::this_thread::sleep_for(std::chrono::microseconds(1000));

    // Write the timestamp and background/signal/"energy" to the CSV file
    output_file << year << "," << month << "," << day << "," << hour << ","
                << minute << "," << second << "," << id << ","
                << background_value << "," << signal_value << "," << energy
                << "\n";
  }
}

// Default one, if called with .x rather than .L
void generate() { generate("random_data.csv", 100000); }
