/*
 *  main.cpp
 *  Profiler
 *
 *  Created by Jonathan Maletic on 11/8/11.
 *  Copyright 2013 Kent State University. All rights reserved.
 *
 *  Requires main.cpp first, followed by other files.
 *
 *  Modified by:
 *
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

#include "ASTree.hpp"
#include "profile.hpp"


//
// Reads a srcML file into an internal data structure.
// Then prints out the data structure.

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Error: One or more input files are required." << std::endl;
        std::cerr << "       The main must be the first argument followed by any other .cpp files.  For example:" << std::endl;
        std::cerr << "profiler main.cpp.xml file1.cpp.xml file2.cpp.xml" << std::endl << std::endl;
        return(1);
    }

    srcML                     code;              //The source code to be profiled.
    std::vector<std::string>  files;             //The list of file names (without .xml)
    std::vector<std::string>  profileNames;      //The list of profile names to be used.

    for (int i = 1; i < argc; ++i) {
      std::string filename = argv[i];   //stores command argument as a string
      files.push_back(filename);     //stores filename in "files" vector set
        filename = filename.substr(0, filename.find(".xml"));      //Remove .xml
        std::replace(filename.begin(), filename.end(), '.', '_');  // Change . to _
        profileNames.push_back(filename);  //adds file name without .xml to a "profileNames" vector set
    }

    std::ifstream inFile(files[0].c_str());    //Read in the main.
    inFile >> code;
    inFile.close();

    code.mainHeader(profileNames);             //Add in main header info
    code.mainReport(profileNames);             //Add in the report
    code.funcCount();                          //Count funciton invocations
    code.lineCount(profileNames[0]);           //Count line invocations

    std::string outFileName = "p-" + files[0];  //creates a new filename from the first in the vector
    outFileName = outFileName.substr(0, outFileName.find(".xml"));  //Remove .xml
    std::ofstream outFile(outFileName.c_str());  //outputs for c++ (without the .xml)
    outFile << code << std::endl;
    outFile.close();

    for (unsigned i = 1; i < files.size(); ++i) {  //Read in the rest of the files.
        inFile.open(files[i].c_str());
        inFile >> code;
        inFile.close();

        code.fileHeader(profileNames);             //Add in file header info
        code.funcCount();                          //Count funciton invocations
        code.lineCount(profileNames[i]);           //Count line invocations

        outFileName = "p-" + files[i];
        outFileName = outFileName.substr(0, outFileName.find(".xml"));  //Remove .xml
        outFile.open(outFileName.c_str());
        outFile << code << std::endl;
        outFile.close();
    }

        return 0;
}
