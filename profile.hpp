/*
 *  profile.hpp
 *
 *  Created by Jonathan Maletic on 3/29/2012.
 *  Copyright 2012 Kent State University. All rights reserved.
 *
 *  Modified by:
 *
 */

#ifndef INCLUDES_PROFILE_H_
#define INCLUDES_PROFILE_H_

#include <iostream>
#include <cassert>
#include <string>
#include <map>
#include <algorithm>

std::string intToString(int);


////////////////////////////////////////////////////////////////////////
//  A map of line numbers or line number function names and the number
//   of times each was called.
//
//
class profile {
public:
           profile ()                     {};
    void   count   (const int line, const std::string& fname) { item[intToString(line) + " " + fname] += 1; }
    void   count   (const int line)                           { item[intToString(line)] += 1; }

    friend std::ostream& operator<< (std::ostream&, const profile&);

private:
    std::map<std::string, int> item;  //Map of items and their counts
};


#endif
