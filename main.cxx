// Use the argumentum external library, requires argumentum to be built to use!
#include <argumentum/argparse.h>

#include "Analysis.h"
#include "DataExtraction.h"
// For the std::cout functionality
#include <iostream>
#include <string>
int main(int argc, char* argv[]) {
  // Create a parser (a small program that translates text from one format into
  // another).
  //
  // Not constant, we want to make changes to it by telling it what command line
  // arguments we are expected
  auto parser = argumentum::argument_parser{};
  // Tell the parser the name of the program (which always can be found from the
  // first element in argv, argv[0]) and give it a description by using the
  // program and description member-functions of parser.config();
  const std::string program_name{argv[0]};
  const std::string program_description{"A demonstration program for MNXB11"};
  // Note: We make this a reference variablen because we want to make
  // changes to the configuration inside the parser object!
  auto parser_configuration{parser.config()};
  parser_configuration.program(program_name);
  parser_configuration.description(program_description);

  // Create an object that represents the different parameters that our program
  // can use.
  //
  // This object has a reference to the parser object internally and will tell
  // the parser about any parameters we set up.
  auto parameters = parser.params();

  // Create our first parameter: The file that we are going to read data from.
  //
  // The variable is not constant because we will want to change it depending on
  // what command line argument the user gives us!
  std::string input_file{};

  // Create a new variable that represents the input file parameter.
  // This will create and configure a new parameter that will write the results
  // from parsing the arguments into the input_file variable (the first argument
  // to add_parameter) which can be accessed by the user by either the -i or
  // --input-file flag at the command line.
  //
  auto input_file_parameter{
      parameters.add_parameter(input_file, "-i", "--input-file")};
  // Tell the parameter that we it should be required, i.e. parsing should fail
  // if it wasn't specified
  input_file_parameter.required(true);
  // Tell the parameter that it expects one and only one value.
  input_file_parameter.nargs(1);
  // Write a helpful description of the parameter for the user
  input_file_parameter.help("The file to read from");

  // Create a second parameter that lets the user specify which analysis to run
  // (if multiple)
  int analysis_choice{};
  auto analysis_choice_parameter{
      parameters.add_parameter(analysis_choice, "-a", "--analysis")};
  analysis_choice_parameter.required(true);

  analysis_choice_parameter.nargs(1);
  // Change what the argument gets called in the help text (compare with
  // input-file version)
  analysis_choice_parameter.metavar("ANALYSIS-CHOICE");
  analysis_choice_parameter.help(
      "Choose which of the project's steps to run: 0 -> Run data extraction "
      "only and persist the raw data, 1 "
      "-> Run analysis 1 (Signal and Background), 2 -> Run analysis 2 (Some "
      "analysis), 3 -> Run analysis 3 (Some other analysis) , 4 -> Run all "
      "three analyses");

  // Run the parser!
  //
  // Note that the argumentum documentation will have an extra argument (1)
  // here which we can ignore. It is related to a feature that we don't use.
  //
  // Documentation version would have looked like this:
  // bool successful_parse{parser.parse_args(argc, argv, 1)};

  bool successful_parse{parser.parse_args(argc, argv)};
  // If you look at what is going on in the debugger, you should see that after
  // the previous line has executed, the input_file variable has been modified.

  if (!successful_parse) {
    // Something was wrong! Argumentum will print some details to the screen by
    // default, we can add more and then exit the program.
    //
    std::cout << "Something went wrong with the argument parsing" << std::endl;

    // Exiting with a value other than 0 means something went wrong
    std::exit(1);
  }
  // Parsing went well, we can continue!

  // Add a new command line parameter to make this customizable by the user!
  const std::string output_file{"results/output.root"};
  // If you are interested, you could look into the C++ feature called enum
  // class which could make this code a lot more readable and maintainable by
  // giving names to the different numbers used here!
  std::cout << "Running data extraction!" << std::endl;
  const auto measurements{read_measurements(input_file)};
  switch (analysis_choice) {
    case 0:
      std::cout << "Persisting raw measurement data to file " << output_file
                << std::endl;
      persist_measurements(measurements, output_file);
      break;
    case 1:
      std::cout << "Running signal/background analysis" << std::endl;
      signal_and_background(measurements, output_file);
      break;
    case 2:
      std::cout << "Running a second analysis" << std::endl;
      some_analysis(measurements, output_file);
      break;
    case 3:
      std::cout << "Running a third analysis" << std::endl;
      some_other_analysis(measurements, output_file);
      break;
    case 4:
      std::cout << "Running all analyzes!" << std::endl;
      signal_and_background(measurements, output_file);
      some_analysis(measurements, output_file);
      some_other_analysis(measurements, output_file);
      break;
    default:
      // We got an invalid analysis choice
      std::cerr << "Analysis choice must be one of either 0, 1, 2, 3, or 4"
                << std::endl;
      std::exit(2);
  }

  return 0;
}
