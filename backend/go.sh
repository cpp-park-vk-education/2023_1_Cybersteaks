# build all targets and start drogon web server
# use 'make test' to start tests

rm -rf build && mkdir build && cd build && cmake -D BUILD_TESTS=ON .. && make
cd ../build && ./increa_proj