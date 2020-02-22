//
// Created by makon on 10/02/2020.
//

#include "Rc522.h"
#include <fstream>


string Rc522::readTag() {

    string UID;
    const char command[] = "python /home/pi/Desktop/F_CITY/Hardware/Read.py";
    std::system(command);
    ifstream file;
    file.open("./output.txt");
    //char output[16];
    if (file.is_open()) {
        while (!file.eof()) {
            file >> UID;
        }
    }
    file.close();
    return (UID);
}
