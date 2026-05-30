#include <cstring>
#include <fstream>

#include "circle.hpp"
#include "group.hpp"
#include "line.hpp"
#include "rectangle.hpp"
#include "shape.hpp"
#include "svgfile.hpp"
#include "utils.hpp"

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
            const char* filename = currFile->getFilename();
            delete currFile;
            currFile = nullptr;
            std::cout << filename << " closed." << std::endl;

        } else if (strcmp(command, "save") == 0) {
            if (!currFile) {
                std::cout << "no file is currently open to save!" << std::endl;
                continue;
            }
            currFile->serialize();
            std::cout << "successfully saved " << currFile->getFilename() << "."
                      << std::endl;

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
            if (!arg) {
                std::cout << "no shape details entered!" << std::endl;
                continue;
            }
            if (!currFile) {
                std::cout << "no file is open!" << std::endl;
                continue;
            }
            // TODO: create shape from arg details
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
            if (!arg) {
                std::cout << "no coordinates entered!" << std::endl;
                continue;
            }
            if (!currFile) {
                std::cout << "no file is open!" << std::endl;
                continue;
            }
            int dx = readInt(arg), dy = readInt(++arg);
            currFile->translate(dx, dy);
            std::cout << "shapes translated by (" << dx << ',' << dy << ")" << std::endl;
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
            // TODO: create shape from arg
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
            // TODO: list numbers and make a new group containing said numbers
            // appended to the end with move semantics
        } else if (strcmp(command, "exit") != 0) {
            std::cout << "unrecognized command: " << command << '!' << std::endl;
        }

    } while (strcmp(command, "exit") != 0);

    std::cout << "exiting program..." << std::endl;
    delete currFile;

    return 0;
}