/*
 *  ASTree.hpp
 *  Abstract Syntax Tree
 *
 *  Created by Jonathan Maletic on 11/8/11.
 *  Copyright 2013 Kent State University. All rights reserved.
 *
 *  Modified by:
 *
 */

#ifndef INCLUDES_ASTree_H_
#define INCLUDES_ASTree_H_

#include <list>
#include <vector>
#include <iostream>
#include <iomanip>
#include <cassert>
#include <algorithm>

class      ASTree;
enum       nodes {category, token, whitespace};   //WHAT IS THIS?
const bool TAGS  = false;

bool                     isStopTag (std::string);
std::string              readUntil (std::istream&, char);
std::string              unEscape  (std::string);
std::vector<std::string> tokenize  (const std::string& s);


////////////////////////////////////////////////////////////////////////
// An ASTree is either a:
//     -Syntactic category node
//     -Token node
//     -Whitespace node
//
// CLASS INV: if (nodeType == category) than (child != 0) && (text == "")
//            if ((nodeType == token) || (nodeType == whitespace)) then (child == 0) && (text != "")
//
class ASTree {
public:
                  ASTree    () {};
                  ASTree    (nodes t) : nodeType(t) {};
                  ASTree    (nodes t, const std::string&);
                  ~ASTree   ();
                  ASTree    (const ASTree&);
    void          swap      (ASTree&);
    ASTree&       operator= (ASTree);
    ASTree*       copyASTree();
    ASTree*       getChild  (std::string);
    std::string   getName   () const;

    void          mainHeader(std::vector<std::string>&);
    void          fileHeader(std::vector<std::string>&);
    void          mainReport(std::vector<std::string>&);
    void          funcCount ();
    void          lineCount (const std::string&);
    std::ostream& print     (std::ostream&, int) const;
    std::istream& read      (std::istream&);

private:
    nodes               nodeType;       //Category, Token, or Whitespace
  //WHAT IS "NODES" AS A TYPE??
  //WHAT CAN IT BE SET TO??
    std::string         tag,            //Category: the tag name and
                        closeTag;       //          closing tag.
    std::list<ASTree*>  child;          //Category: A list of subtrees.
    std::string         text;           //Token/Whitespace: the text.
};


////////////////////////////////////////////////////////////////////////
// srcML is an internal data structure for a srcML input file.
// CLASS INV: Assigned(tree)
//
class srcML {
public:
            srcML     () : tree(0) {};
            ~srcML    ()           {delete tree;}
            srcML     (const srcML&);
    void    swap      (srcML&);
    srcML&  operator= (srcML);

    void    mainHeader(std::vector<std::string>&);
    void    fileHeader(std::vector<std::string>&);
    void    mainReport(std::vector<std::string>&);
    void    funcCount ();
    void    lineCount (const std::string&);

    friend  std::istream& operator>>(std::istream&, srcML&);
    friend  std::ostream& operator<<(std::ostream&, const srcML&);

private:
    std::string  header;
    ASTree*      tree;
};




#endif
