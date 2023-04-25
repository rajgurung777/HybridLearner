# install prerequisites

cd libraries/

# Installation library UnitTest++

git clone https://github.com/unittest-cpp/unittest-cpp
cd unittest-cpp/
git checkout v2.0.0 

cd builds
cmake -G "Eclipse CDT4 - Unix Makefiles" ../
cmake --build ./
sudo cmake --build ./ --target install
cd ../../../


