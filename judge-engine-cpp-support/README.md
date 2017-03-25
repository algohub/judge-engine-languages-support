# judge-engine-cpp-support

code to support C++


## How to compile

Compile and install Google Test first,

    git@github.com:google/googletest.git
    mkdir ~/tmp
    cd ~/tmp
    sudo apt install cmake
    cmake /home/programmer/github/googletest/googletest
    make
    sudo make install

Then use `cmake` to compile this project,

    cd judge-engine-cpp-support
    $(clion_install_dir)/bin/cmake/bin/cmake .

then use Clion to open `CMakeLists.txt`, Clion will import this project automatically.

