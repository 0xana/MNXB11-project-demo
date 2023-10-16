#include <TFile.h>
#include <TH1D.h>

#include <string>

// Fitting code from the ROOT FittingDemo
#include "TCanvas.h"
#include "TF1.h"
#include "TH1.h"
#include "TLegend.h"
#include "TMath.h"

// Quadratic background function
Double_t background(Double_t *x, Double_t *par) {
  return par[0] + par[1] * x[0] + par[2] * x[0] * x[0];
}

// Lorenzian Peak function
Double_t lorentzianPeak(Double_t *x, Double_t *par) {
  return (0.5 * par[0] * par[1] / TMath::Pi()) /
         TMath::Max(1.e-10,
                    (x[0] - par[2]) * (x[0] - par[2]) + .25 * par[1] * par[1]);
}

// Sum of background and peak function
Double_t fitFunction(Double_t *x, Double_t *par) {
  return background(x, par) + lorentzianPeak(x, &par[3]);
}

void signal_and_background(const std::string &input_filename) {
  TFile file{input_filename.c_str(), "READ"};
  TH1D *histogram{static_cast<TH1D *>(file.Get("signal_and_background"))};

  TCanvas *canvas = new TCanvas("c1", "Fitting Demo", 10, 10, 700, 500);
  canvas->SetGrid();

  // A fit function using the combined lorentz peak on a quadratic background
  // defined above with 6 parameters, defined between 0 and 3 on the x-axis
  TF1 *fit_function{new TF1{"lorentzian_on_quadratic", fitFunction, 0, 3, 6}};
  fit_function->SetLineColor(kMagenta);
  fit_function->SetLineWidth(4);

  // first try without starting values for the parameters
  // This defaults to 1 for each param.
  // this results in an ok fit for the polynomial function
  // however the non-linear part (lorenzian) does not
  // respond well.
  fit_function->SetParameters(1, 1, 1, 1, 1, 1);
  // Second argument is how verbose the output should be
  // Third argument are style arguments for how to draw the histogram
  histogram->Fit("lorentzian_on_quadratic", "V+", "ep");

  // Functions for the two components using the parameters from the fit
  // Each with 3 parameters defined between 0 and 3 on the x-axis
  TF1 *background_function{
      new TF1{"quadratic_background", background, 0, 3, 3}};
  background_function->SetLineColor(kRed);

  TF1 *signal_function{new TF1{"signal", lorentzianPeak, 0, 3, 3}};
  signal_function->SetLineColor(kBlue);

  std::array<Double_t, 6> parameters{};  // An array with 6 double values
  // Write the fit results into the parameters array
  fit_function->GetParameters(parameters.data());

  // The SetParameters function takes a pointer to the location where we want to
  // read the function parameters from.
  // First three: 0, 1, and 2 are the background parameters
  background_function->SetParameters(&parameters[0]);
  // Last three: 3, 4, and 5 are the signal parameters
  signal_function->SetParameters(&parameters[3]);

  background_function->Draw("SAME");
  signal_function->Draw("SAME");

  TLegend *legend{new TLegend{0.6, 0.65, 0.88, 0.85}};
  legend->SetTextFont(72);
  legend->SetTextSize(0.04);
  legend->AddEntry(histogram, "Data", "lpe");
  legend->AddEntry(background_function, "Background fit", "l");
  legend->AddEntry(signal_function, "Signal fit", "l");
  legend->AddEntry(fit_function, "Global Fit", "l");
  legend->Draw();

  canvas->SaveAs("figures/SignalAndBackground.pdf");
}

// Default file name version
void signal_and_background() { signal_and_background("results/output.root"); }
