/*
 *  ASTree.cpp
 *  Abstract Syntax Tree
 *
 *  Created by Jonathan Maletic on 11/8/11.
 *  Copyright 2013 Kent State University. All rights reserved.
 *
 *  Modified by:
 *
 */

#include "ASTree.hpp"


/////////////////////////////////////////////////////////////////////
// Copy constructor for srcML
//
srcML::srcML(const srcML& actual) {
    tree = new ASTree(*(actual.tree));
}

/////////////////////////////////////////////////////////////////////
// Constant time swap for srcML
//
void srcML::swap(srcML& b) {
    std::string t_header = header;
    header = b.header;
    b.header = t_header;

    ASTree *temp = tree;
    tree = b.tree;
    b.tree = temp;
}

/////////////////////////////////////////////////////////////////////
// Assignment for srcML
//
srcML& srcML::operator=(srcML rhs) {
    swap(rhs);
    return *this;
}

/////////////////////////////////////////////////////////////////////
// Reads in and constructs a srcML object.
//
std::istream& operator>>(std::istream& in, srcML& src){
    char ch;
    if (!in.eof()) in >> ch;
    src.header = readUntil(in, '>');
    if (!in.eof()) in >> ch;
    if (src.tree) delete src.tree;
    src.tree = new ASTree(category, readUntil(in, '>'));
    src.tree->read(in);
    return in;
}


/////////////////////////////////////////////////////////////////////
// Prints out a srcML object
//
std::ostream& operator<<(std::ostream& out, const srcML& src){
    if (TAGS) out << "<" << src.header << ">" << std::endl;
    src.tree->print(out, 0);
    return out;
}




/////////////////////////////////////////////////////////////////////
//  Adds in the includes and profile variables
//
void srcML::mainHeader(std::vector<std::string>& profileNames) {
    tree->mainHeader(profileNames);
}

/////////////////////////////////////////////////////////////////////
//  Adds in the includes and profile variables
//
void srcML::fileHeader(std::vector<std::string>& profileNames) {
    tree->fileHeader(profileNames);
}


/////////////////////////////////////////////////////////////////////
// Adds in the report to the main.
//
void srcML::mainReport(std::vector<std::string>& profileNames) {
        tree->mainReport(profileNames);
}

/////////////////////////////////////////////////////////////////////
//  Inserts a function.count() into each function body.
//
void srcML::funcCount() {
    tree->funcCount();
}

/////////////////////////////////////////////////////////////////////
// Inserts a filename.count() for each statement.
//
void srcML::lineCount(const std::string& profilename) {
    tree->lineCount(profilename);
}


//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//                                                      //
//              End srcML functions                     //
//              Begin ASTree functions                  //
//                                                      //
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////
// Constructs a category, token, or whitespace node for the tree.
//
ASTree::ASTree(nodes t, const std::string& s) {
    nodeType = t;
    switch (nodeType) {
        case category:
            tag = s;
            break;
        case token:
            text = unEscape(s);
            break;
        case whitespace:
            text = s;
            break;
    }
}



////////////////////////////////////////////////////////////////////
//Deconstructor for ASTree
//
ASTree::~ASTree() {
  std::list<ASTree*>::iterator tracker = child.begin();  //WHERE DO THE BEGIN AND END FUNCTIONS COME FROM??
                                                         //WHAT DO THEY DO/HOW DO THEY WORK?
  while (tracker != child.end()) { //while not the last child
    delete *tracker;               //delete what the iterator is pointing to
    ++tracker;                     //advance the iterator
  }
}



/////////////////////////////////////////////////////////////////////
// Copy Constructor for ASTree
//
ASTree::ASTree(const ASTree& actual) {
  nodeType = actual.nodeType;     //copy over nodeType
  tag = actual.tag;               //and tag
  closeTag = actual.closeTag;     //and closeTag
  text = actual.text;             //and text

  std::list<ASTree*>::const_iterator tracker = actual.child.begin();
  while (tracker != actual.child.end()) {
    ASTree *temp = new ASTree(*(*tracker)); //SLIGHTLY CONFUSED BY MULTIPLE *'S
                                            //IS IT POINTING TO THE NODE THAT THE ITERATOR IS POINTING TO?
    child.push_back(temp); //I'M ASSUMING THE PUSH_BACK FUCTION IS WHAT ADDS THE NODE TO THE TREE?
    ++tracker;
  }
}


/////////////////////////////////////////////////////////////////////
// Constant time swap for ASTree
//
void ASTree::swap(ASTree& b) {
  nodes tempNodeType = nodeType;  //stores node type in a temp
  nodeType = b.nodeType;  //changes nodeType
  b.nodeType = tempNodeType;  //changes b.NodeType

  //HOW ARE YOU CALLING SWAP ON ITSELF??
  //IF IT WAS RECURSIVE, IT WOULD NEED A STOPPING CASE, RIGHT?
  //OR DOES THIS USE A DIFFERENT SWAP FUNCTION?
  tag.swap(b.tag);
  closeTag.swap(b.closeTag);
  text.swap(b.text);
  child.swap(b.child);
}

/////////////////////////////////////////////////////////////////////
// Assignment for ASTree
//
ASTree& ASTree::operator=(ASTree rhs) {
    swap(rhs);
    return *this;
}




/////////////////////////////////////////////////////////////////////
// Returns an this->child[i] where (this->child[i]->tag == tagName)
//
ASTree* ASTree::getChild(std::string tagName) {
    std::list<ASTree*>::iterator ptr = child.begin();
    while (((*ptr)->tag != tagName) && (ptr != child.end())) {
         ++ptr;
    }
    return *ptr;
}



/////////////////////////////////////////////////////////////////////
// Returns the full name of a <name> node.
//
std::string ASTree::getName() const {
    std::string result;
    if (child.front()->tag != "name") {
        result = child.front()->text;   //A simple name (e.g., main)
    } else {                              //A complex name (e.g., stack::push).
        result = child.front()->child.front()->text;
        result += "::";
        result += child.back()->child.front()->text;
    }
    return result;
}




/////////////////////////////////////////////////////////////////////
//  Adds in the includes and profile variables in a main file.
//
void ASTree::mainHeader(std::vector<std::string>& profileNames) {

    //NEED TO IMPLEMENT
    //Skip down a couple lines.
    //For each file profile name, add a new node with a profile
    // declaration.
    //Also, add in the profile declaration for functions and the
    //include for profile.hpp
}


/////////////////////////////////////////////////////////////////////
//  Adds in the includes and profile variables for non-main files
//
void ASTree::fileHeader(std::vector<std::string>& profileNames) {

    //NEED TO IMPLEMENT
    //Skip down a couple lines.
    //For each file profile name, add a new node with a profile
    // extern declaration.
    //Also, add in the extern declaration for functions and the
    //include for profile.hpp


}


/////////////////////////////////////////////////////////////////////
// Adds in the report to the main.
// Assumes only one return at end of main body.
//
void ASTree::mainReport(std::vector<std::string>& profileNames) {

    //NEED TO IMPLEMENT

    //Find the function with name main and then start from the end.
    //Find the main - function with name of "main"
    //Then start from the end() of this function and iterate
    // backwards until you find a return stmt.   You'll want
    // to insert the report statements before this return.


}


/////////////////////////////////////////////////////////////////////
// Adds in a line to count the number of times each function is executed.
//  Assumes no nested functions.
//
void ASTree::funcCount() {

    //NEED TO IMPLEMENT

    // Check for function, constructor, destructor.
    // Find the function name and insert the count.

}

/////////////////////////////////////////////////////////////////////
// Adds in a line to count the number of times each statement is executed.
//   No breaks, returns, throw etc.
//   Assumes all construts (for, while, if) have { }.
//
void ASTree::lineCount(const std::string& profileNames) {

    //NEED TO IMPLEMENT

    // Check for expr_stmt and call


}


/////////////////////////////////////////////////////////////////////
// Read in and construct ASTree
// REQUIRES: '>' was previous charater read
//           && this == new ASTree(category, "TagName")
//
//
std::istream& ASTree::read(std::istream& in) {
    ASTree *subtree;
    std::string temp, Lws, Rws;
    char ch;
    if (!in.eof()) in.get(ch);
    while (!in.eof()) {
        if (ch == '<') {                                     //Found a tag
            temp = readUntil(in, '>');
            if (temp[0] == '/') {
                closeTag = temp;
                break;                                       //Found close tag, stop recursion
            }
            subtree = new ASTree(category, temp);            //New subtree
            subtree->read(in);                               //Read it in
            in.get(ch);
            child.push_back(subtree);                        //Add it to child
        } else {                                             //Found a token
            temp = std::string(1, ch) + readUntil(in, '<');  //Read it in.
            std::vector<std::string> tokenList = tokenize(temp);
            for (std::vector<std::string>::const_iterator i = tokenList.begin(); i != tokenList.end(); ++i) {
                if (isspace((*i)[0])) {
                    subtree = new ASTree(whitespace, *i);
                } else {
                    subtree = new ASTree(token, *i);
                }
                child.push_back(subtree);
            }
            ch = '<';
        }
    }
    return in;
}


/////////////////////////////////////////////////////////////////////
// Print an ASTree
// REQUIRES: indent >= 0
//
std::ostream& ASTree::print(std::ostream& out, int indent) const {
    if (TAGS) out << std::setw(indent) << " ";
    if (TAGS) out << "<" << tag << ">" << std::endl;
    for (std::list<ASTree*>::const_iterator i = child.begin(); i != child.end(); ++i) {
        switch ((*i)->nodeType) {
            case category:
                (*i)->print(out, indent + 4);
                break;
            case token:
                //out << std::setw(indent) << " ";
                out << (*i)->text; // << std::endl;
                break;
            case whitespace:
                out << (*i)->text;
                break;
        }
    }
    if (TAGS) out << std::setw(indent) << " ";
    if (TAGS) out << "<" << closeTag << ">" << std::endl;
    return out;
}





/////////////////////////////////////////////////////////////////////
// Utilities
//

bool isStopTag(std::string tag) {
    if (tag == "decl_stmt") return true;
    if (tag == "argument_list") return true;
    if (tag == "init") return true;
    if (tag == "condition") return true;
    if (tag == "cpp:include") return true;
    if (tag == "comment type\"block\"") return true;
    if (tag == "comment type\"line\"") return true;
    if (tag == "macro") return true;

    return false;
}

/////////////////////////////////////////////////////////////////////
// Reads until a key is encountered.  Does not include ch.
// REQUIRES: in.open()
// ENSURES: RetVal[i] != key for all i.
//
std::string readUntil(std::istream& in, char key) {
    std::string result;
    char ch;
    in.get(ch);
    while (!in.eof() && (ch != key)) {
        result += ch;
        in.get(ch);
    }
    return result;
}

/////////////////////////////////////////////////////////////////////
// Converts escaped XML charaters back to charater form
// REQUIRES: s == "&lt;"
// ENSURES:  RetVal == "<"
//
std::string unEscape(std::string s) {
    std::size_t pos = 0;
    while ((pos = s.find("&gt;"))  != s.npos) { s.replace(pos, 4, ">");}
    while ((pos = s.find("&lt;"))  != s.npos) { s.replace(pos, 4, "<");}
    while ((pos = s.find("&amp;")) != s.npos) { s.replace(pos, 5, "&");}
    return s;
}


/////////////////////////////////////////////////////////////////////
// Given: s == "   a + c  "
// RetVal == {"   ", "a", " ", "+", "c", " "}
//
std::vector<std::string> tokenize(const std::string& s) {
    std::vector<std::string> result;
    std::string temp = "";
    unsigned i = 0;
    while (i < s.length()) {
        while (isspace(s[i]) && (i < s.length())) {
            temp.push_back(s[i]);
            ++i;
        }
        if (temp != "") {
            result.push_back(temp);
            temp = "";
        }
        while (!isspace(s[i]) && (i < s.length())) {
            temp.push_back(s[i]);
            ++i;
        }
        if (temp != "") {
            result.push_back(temp);
            temp = "";
        }
    }
    return result;
}
