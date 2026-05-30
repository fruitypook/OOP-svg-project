#include <cstring>
#include <fstream>

#include "circle.hpp"
#include "group.hpp"
#include "line.hpp"
#include "rectangle.hpp"
#include "shape.hpp"
#include "svgfile.hpp"
#include "utils.hpp"

void loadTestFile(SVGFile& f) {
    Line* l = new Line({100, 10}, {70, 0}, {100, 0, 0});
    Rectangle* r = new Rectangle({200, 100}, 150, 40, {0, 100, 0}, {100, 0, 100});
    Circle* c = new Circle({50, 60}, 30, {100, 100, 0}, {0, 0, 100});

    f.addShape(l), f.addShape(r), f.addShape(c);

    Group* g1 = new Group();

    Group* g2 = new Group();
    g2->addShape(r).addShape(l);

    g1->addShape(l);
    g1->addShape(g2);
    g1->addShape(c);

    f.addShape(g1);

    delete l;
    delete r;
    delete c;
    delete g1;
    delete g2;
}

void printHelpMsg() {
    std::cout << "The following commands are supported:\n"
              << "open <file>   \t opens <file> \n"
              << "close         \t closes currently opened file \n"
              << "save          \t saves the currently open file \n"
              << "saveas <file> \t saves the currently open file in <file> \n"
              << "help          \t prints this information exit exists the program \n"
              << "exit          \t exits the program" << std::endl;
}

char* nextWord(char* src) {
    if (!src) return nullptr;
    while (*src != '\0' && *src != ' ') ++src;
    if (*src == ' ' && *src != '\0') {
        *(src++) = '\0';
        while (*src == ' ') ++src;
    }
    if (*src == '\0') return nullptr;  // src is only one word
    return src;
}

constexpr unsigned CommandBufferSize = 128;
void inputCommandAndArgs(char*& command, char*& arg, char* buffer) {
    command = buffer, arg = buffer;  // resets position to start of buffer
    std::cin.getline(buffer, CommandBufferSize);
    arg = nextWord(command);
}

// int main() {
//     std::cout << "hai!" << std::endl;

//     SVGFile f("testshape.svg");
//     f.deserialize();

//     for (int i = 0; i < 80; ++i) std::cout << '-';
//     std::cout << std::endl;

//     f.print();

//     for (int i = 0; i < 80; ++i) std::cout << '-';
//     std::cout << std::endl;
// }

int main() {
    std::cout << "hai!" << std::endl;

    char buffer[CommandBufferSize],  //
        *command = buffer, *arg = buffer;

    // nullptr = no file is currently open
    SVGFile* currFile = nullptr;

    // TODO: commands
    do {
        std::cout << '>';
        inputCommandAndArgs(command, arg, buffer);

        std::cout << "cmd:" << command << std::endl;
        if (arg) std::cout << "arg:" << arg << std::endl;

        if (strcmp(command, "open") == 0) {
            if (!arg) {
                std::cout << "no file name entered!" << std::endl;
                continue;
            }
            if (currFile) {
                std::cout << "a file is already open! close it before opening another."
                          << std::endl;
                continue;
            }
            currFile = new SVGFile(arg);
            currFile->deserialize();
            std::cout << "opened " << arg << std::endl;
        } else if (strcmp(command, "close") == 0) {
            if (!currFile) {
                std::cout << "no file currently open to close!" << std::endl;
                continue;
            }
            delete currFile;
            currFile = nullptr;
            std::cout << arg << " closed." << std::endl;

        } else if (strcmp(command, "save") == 0) {
            if (!currFile) {
                std::cout << "no file is currently open to save!" << std::endl;
                continue;
            }
            currFile->serialize();
            std::cout << "successfully saved" << arg << "." << std::endl;

        } else if (strcmp(command, "saveas") == 0) {
            if (!arg) {
                std::cout << "no file name entered!" << std::endl;
                continue;
            }
            if (!currFile) {
                std::cout << "no file currently open to save!" << std::endl;
                continue;
            }

            currFile->serializeToFile(arg);
            std::cout << "saved a copy as " << arg << '.' << std::endl;
        } else if (strcmp(command, "help") == 0) {
            printHelpMsg();
        } else if (strcmp(command, "print") == 0) {
            if (!currFile) {
                std::cout << "no file currently open to save!" << std::endl;
                continue;
            }
            currFile->print();
        } else if (strcmp(command, "create") == 0) {
            std::cout << "CREATE" << std::endl;
            if (!arg) {
                std::cout << "no shape details entered!" << std::endl;
                continue;
            }
            if (!currFile) {
                std::cout << "no file is open!" << std::endl;
                continue;
            }
            // create shape from arg details
            // add to SVGFile using move semantics
        } else if (strcmp(command, "erase") == 0) {
            if (!arg) {
                std::cout << "no shape number entered!" << std::endl;
                continue;
            }
            if (!currFile) {
                std::cout << "no file is open!" << std::endl;
                continue;
            }
            unsigned pos = readUnsigned(arg);
            currFile->removeShape(pos);
        } else if (strcmp(command, "translate") == 0) {
            std::cout << "TRANS" << std::endl;
            if (!arg) {
                std::cout << "no coordinates entered!" << std::endl;
                continue;
            }
            if (!currFile) {
                std::cout << "no file is open!" << std::endl;
                continue;
            }
            // enter dx dy arguments for translate function;
            int dx, dy;
            currFile->translate(dx, dy);
        } else if (strcmp(command, "within") == 0) {
            std::cout << "WITHIN" << std::endl;
            if (!arg) {
                std::cout << "no container shape entered!" << std::endl;
                continue;
            }
            if (!currFile) {
                std::cout << "no file is open!" << std::endl;
                continue;
            }
            // create shape from arg
            // iterate file and use isWithin or whatever it's called
        } else if (strcmp(command, "group") == 0) {
            if (!arg) {
                std::cout << "no shape numbers entered!" << std::endl;
                continue;
            }
            if (!currFile) {
                std::cout << "no file is open!" << std::endl;
                continue;
            }
            // list numbers with space and make a new group containing said numbers
            // appended to the end with move semantics
        } else if (strcmp(command, "exit") != 0) {
            std::cout << "unrecognized command: " << command << '!' << std::endl;
        }

    } while (strcmp(command, "exit") != 0);

    delete currFile;

    std::cout << "exiting program..." << std::endl;

    return 0;
}