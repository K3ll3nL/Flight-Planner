#define CATCH_CONFIG_RUNNER
#include <fstream>
#include <iostream>
#include "catch.hpp"
#include "Runner.h"

int main(int argc, char** argv) {
    if(argc==1) {
        Catch::Session().run();
    }else {
        std::ofstream outputstream(argv[3]);
        //outputstream << "Hello, World!" << std::endl;
        outputstream.close();
        //std::cout << "Hello and wrote sample output file." << std::endl;
        Runner* test = new Runner();
        test->Run(argv);
        return 0;
    }
}

