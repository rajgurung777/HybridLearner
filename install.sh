# install prerequisites

sudo apt -y update
sudo apt -y install git build-essential libssl-dev wget cmake lzip 

sudo apt-get -y install python3-pip
sudo pip3 install pipenv

#making a directory to store the prerequisites libraries

mkdir ./libraries
cd ./libraries

# install openjdk17

sudo apt -y install openjdk-17-jre-headless
echo


# install Boost
X=$(find /usr/local/include/boost)
if test -z "$X"
then
	sudo wget https://boostorg.jfrog.io/artifactory/main/release/1.79.0/source/boost_1_79_0.tar.gz
	tar -xvf boost_1_79_0.tar.gz
  cd boost_1_79_0/
  ./bootstrap.sh
  ./b2
  cd ..
  sudo ln -sf $PWD/boost_1_79_0/boost /usr/local/include/
  sudo ln -sf $PWD/boost_1_79_0/stage/lib/*.* /usr/local/lib/
else
	echo "Found BOOST Library."
fi


# [OPTIONAL] install nlohmann-json-dev - JSON for Modern C++ 
sudo apt -y install nlohmann-json3-dev

# [OPTIONAL] install plotutils
sudo apt -y install plotutils


# installing and testing submodule for learning HA
cd ../src/learnHA
pipenv install --dev
cd ../..


# installing C shell for MATLAB engine
sudo apt install csh


# Set library path using environment variable to include boost and MATLAB libraries.
# Please change the ***Matlab path as per your installation setup, in my case it is under /usr/local/MATLAB/R2021aUpdate8 ***.
# I recommend to add this to your .bashrc file as well
export MATLAB_INCLUDE_PATH=/usr/local/MATLAB/R2021aUpdate8/extern/include
export MATLAB_LIBRARY_PATH_1=/usr/local/MATLAB/R2021aUpdate8/extern/bin/glnxa64
export MATLAB_LIBRARY_PATH_2=/usr/local/MATLAB/R2021aUpdate8/bin/glnxa64
export MATLAB_LIBRARY_PATH_3=/usr/local/MATLAB/R2021aUpdate8/extern/lib/glnxa64
export MATLAB_STDCPP_PATH=/usr/local/MATLAB/R2021aUpdate8/sys/os/glnxa64/orig/libstdc++.so.6
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/lib:/usr/local/lib:/usr/lib/x86_64-linux-gnu:/usr/local/MATLAB/R2021aUpdate8/bin/glnxa64:/usr/local/MATLAB/R2021aUpdate8/bin/glnxa64/builtins/sl_main/:/usr/local/MATLAB/R2021aUpdate8/extern/bin/glnxa64:/usr/local/MATLAB/R2021aUpdate8/extern/lib/glnxa64:/usr/local/MATLAB/R2021aUpdate8/sys/os/glnxa64
export PATH=$PATH:/usr/lib/x86_64-linux-gnu/glib-2.0/:/usr/bin:/usr/local/MATLAB/R2021aUpdate8/bin

# Compiling the tool HybridLearner
echo "building HybridLearner ..."
cd ./build
sudo make all

# Testing installation by executing the help menu of the tool.
echo
./HybridLearner --help


