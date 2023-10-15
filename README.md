# About

This repository holds a short demonstration of how you can set up a project for MNXB11 as suggested in the Project description. It includes examples of 

- Using a library to parse command line arguments 
- Writing a basic class to represent some physical result and doing rudimentary validation 
- A demonstration of why you *don't* want to write CSV parsing code yourself 
  - The code has at least one bug intentionally, don't use it! Use a library for reading CSV data. 
- Writing data to a ROOT TTree 
- Creating basic histograms with ROOT 
- A Makefile that has all the settings needed to compile the project while linking to both ROOT and the CLI library 
- A small dataset comprised of a CSV file with a lot of unnecessary data similar to that in the histogram from the fitting part of Lecture 7 
- A rootlogon.C macro with some minor style settings 

The demonstration is not intended to be exhaustive or something that you can copy directly, use it as a reference point for the structure and contents. For example, this demonstration does not check that the CLI arguments are valid. There also is no real physics in this demonstration. 

# Build instructions 

The following commands should be executed from the root directory of the demonstration.

## Build and install the argumentum library
``` sh

# -p means create any parent directories if they don't already exist 
# -v means verbose, tell the user what directories were created
# Create a build directory for the command line argument tool 
mkdir -pv build/argumentum 

# Download the external library responsible for handling command line arguments into a directory called argumentum 

git clone https://github.com/mmahnic/argumentum 

# Go into the build directory for argumentum 
cd build/argumentum 
# Configure the build directory with CMake to install files into the external directory 
cmake ../../argumentum -DCMAKE_INSTALL_PREFIX=../../external
# Build and install the library (change the argument to -j to the number of cores you want)
# Adding VERBOSE=1 afterwards sets the VERBOSE variable in the Makefile that cmake produced which will show all the commands that make runs for us. By default, CMake will hide them for us to not spam the terminal too much.
make -j4 install VERBOSE=1
```

## Build the project demo 

Having built and installed the argumentum library you can build and run the project as (remember that you need to be in the container environment to have access to ROOT!)

``` sh
# Create the output directories 
# Hint: Can you get Make to do this for you?  
mkdir -v figures results 
# Build the project 
make 
# Get help from the CLI library 
./main --help
# Write the raw data from the CSV file to the output ROOT file
./main --input-file data/random_data.csv --analysis 0
# Run the implemented analysis 
./main --input-file data/random_data.csv --analysis 1 

# Run the ROOT macro to make a histogram with some manual styling and fits from the analysis 
root macros/signal_and_background.C 
# In the ROOT prompt
> signal_and_background("results/output.root")

# Look at the raw data and histograms stored in the ROOT file 
# Can you spot the bug? 
rootbrowse results/output.root 

```


