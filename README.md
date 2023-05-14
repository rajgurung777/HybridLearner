# HybridLearner: Learn Hybrid Systems for Cyber-Physical Systems.
HybridLearner: is a research tool for learning complex Cyber-Physical Systems. 
Our algorithm leverages automaton learning to approximate black-box hybrid systems, streamlining the modeling and testing process. 
Analyze learned models along with additional features such as Simulink model simulation and model transformation from simple text to .SLX format, and checking equivalence of Simulink model files.

## Installation

HybridLearner is implemented in C++ using MATLAB/Simulink and Python. 
We have used MATLAB version R2021a.  
We suppose HybridLearner works on many UNIX-like operating systems. 
We have tested HybridLearner on Ubuntu 18.04 and **Ubuntu 20.04**. 
However, Ubuntu 18.04 requires installing **python 3.8** or above since **Ubuntu 18.04** comes with **python 2.7** by default.

### Requirements for building HybridLearner from source
For building HybridLearner from source, install the following third-party libraries:
- Boost C++ Libraries
  - The latest package can be downloaded from https://www.boost.org/
- nlohmann-json3-dev - JSON for Modern C++
- numpy
- scikit-learn
- scipy
- matplotlib
- pytest
- fastdtw
  - See https://pypi.org/project/fastdtw/ to install and learn to use the interface.



### Building 
Compiling HybridLearner from Source:

While installing libraries, allow default installation of the library header files into the directory /usr/local/include and the .a/.so files into the directory /usr/local/lib

***To compile the source type:***
```sh
cd build
sudo make all
```
The tool executable with the name HybridLearner will be created in the build directory.

***Running HybridLearner***
- Running HybridLearner requires JDK 17 or higher installed and set as default.


#### To see the help menu of the tool, run:
```sh
./HybridLearner --help
```
***********

## Alternative Installation
To automatically install all the pre-requsites and compile the HybridLearner code, execute the scrip file using the command:
```sh
./install.sh
```

## Instructions:

    Note: Modify the MATLAB library and include paths to match your local installation before running the install.sh script. 
          This ensures that the project can locate the necessary MATLAB libraries and headers during the installation process.

    Note: Submodule (https://github.com/rajgurung777/learnHA) is required.
          This project includes a submodule located at https://github.com/rajgurung777/learnHA. 
          If you download the project as a .zip file, the submodule might not be included. 
          To ensure the submodule is present, please follow these steps:
          - Manually download the learnHA submodule from the provided URL.
          - Extract the contents of the learnHA submodule into the HybridLearner/src folder of this project.
          - After completing the submodule setup, execute the ./install.sh command to finalize the installation process.


