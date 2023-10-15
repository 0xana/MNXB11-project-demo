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


# Dataset 

