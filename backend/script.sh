rm -rf build
mkdir build
cd build
cmake -D BUILD_TESTS=ON ..
make