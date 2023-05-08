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


#set library path env variable to include boost. Please change the ***Matlab path as per your installation setup***.
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/lib:/usr/local/lib:/usr/local/lib/x86_64-linux-gnu:/usr/local/MATLAB/R2021a/bin/glnxa64:/usr/local/MATLAB/R2021a/extern/bin/glnxa64:/usr/local/MATLAB/R2021a/extern/lib/glnxa64:/usr/local/MATLAB/R2021a/sys/os/glnxa64

export PATH=$PATH:/usr/lib/x86_64-linux-gnu/glib-2.0/:/usr/bin:/usr/local/MATLAB/R2021a/bin

# Compiling the tool HybridLearner
echo "building HybridLearner ..."
cd ./build
sudo make all

# Testing installation by executing the help menu of the tool.
echo
./HybridLearner --help


