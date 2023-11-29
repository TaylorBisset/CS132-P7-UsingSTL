// main.cpp

/*
Name:           Taylor Bisset
Section:        A
Program Name:   CS132-P7-UsingSTL

Description:    This program utilizes C++ Standard Template Library (STL) 
                 algorithms to process and manipulate sets of strings read from input files. 
                The primary objectives include implementing a `punctRemover` function
                 to remove punctuation from strings, 
                 creating an `AscDictSort` functor for ascending dictionary sort 
                 while ignoring case, and performing set operations.

Repo:           https://github.com/TaylorBisset/CS132-P7-UsingSTL 

*/

#include <iostream>
#include <algorithm>
#include <set>
#include <string>
#include <iterator>
#include <fstream>
#include <cctype>

using namespace std;

string punctRemover(const string& strIn); // function prototype

// Functor for ascending dictionary sort, ignoring case.
class AscDictSort
{
public:
    bool operator () (const string& str1, const string& str2) const
    {
        string lowerStr1 = toLower(str1);
        string lowerStr2 = toLower(str2);

        return lowerStr1 < lowerStr2;
    }
private:
    string toLower(const string& str) const
    {
        string result;
        for (char ch : str)
        {
            result.push_back(tolower(ch));
        }
        return result;
    }
};

int main()
{
    set<string, AscDictSort> set1;
    set<string, AscDictSort> set2;
    set<string, AscDictSort> modSet1;
    set<string, AscDictSort> modSet2;

    // transform(ilist.begin( ), ilist.end( ), back_inserter(ilist2), sqr );   // transform example
    ifstream infile1("infile1.txt");
    transform(istream_iterator<string>(infile1), istream_iterator<string>(), inserter(set1, set1.begin()), punctRemover);
    //        input stream from infile1.txt    , end of infile1.txt        , insert into set1            , remove punctuation
    infile1.close();

    ifstream infile2("infile2.txt");
    transform(istream_iterator<string>(infile2), istream_iterator<string>(), inserter(set2, set2.begin()), punctRemover);
    //        input stream from infile2.txt    , end of infile2.txt        , insert into set2            , remove punctuation
    infile2.close();

    cout << "*** Size of sets ***\n";
    cout << "Size of set1:    " << set1.size() << endl;
    cout << "Size of set2:    " << set2.size() << endl;
    cout << "Size of modSet1: " << modSet1.size() << endl;
    cout << "Size of modSet2: " << modSet2.size() << endl;
    cout << endl;

    modSet1 = set1;
    modSet2 = set2;

    cout << "*** Sizes after copying ***\n";
    cout << "Size of set1:    " << set1.size() << endl;
    cout << "Size of set2:    " << set2.size() << endl;
    cout << "Size of modSet1: " << modSet1.size() << endl;
    cout << "Size of modSet2: " << modSet2.size() << endl;
    cout << endl;

    for (const auto& str : set2) // remove strings from modSet1
    {
        modSet1.erase(str);
    }
    for (const auto& str : set1) // remove strings from modSet2
    {
        modSet2.erase(str);
    }

    cout << "*** Sizes after removals ***\n";
    cout << "Size of set1:    " << set1.size() << endl;
    cout << "Size of set2:    " << set2.size() << endl;
    cout << "Size of modSet1: " << modSet1.size() << endl;
    cout << "Size of modSet2: " << modSet2.size() << endl;

    ofstream outfile1("outfile1.txt");
    copy(modSet1.begin(), modSet1.end(), ostream_iterator<string>(outfile1, " "));
    outfile1.close();
    ofstream outfile2("outfile2.txt");
    copy(modSet2.begin(), modSet2.end(), ostream_iterator<string>(outfile2, " "));
    outfile2.close();

    return 0;
}

// Function to remove punctuation from a string, keeping only alphanumeric characters and single quotes.
string punctRemover(const string& strIn) 
{
    string result;
    for (char ch : strIn)
    {
        if (isalnum(ch) || ch == '\'') // keep alphanumeric characters and single quotes
        {
            result.push_back(ch);
        }
    }
    return result;
}


/*
OUTPUT: 

*** Size of sets ***
Size of set1:    1354
Size of set2:    967
Size of modSet1: 0
Size of modSet2: 0

*** Sizes after copying ***
Size of set1:    1354
Size of set2:    967
Size of modSet1: 1354
Size of modSet2: 967

*** Sizes after removals ***
Size of set1:    1354
Size of set2:    967
Size of modSet1: 991
Size of modSet2: 604

*/

/*

Details 

Using the STL Algorithms and with your code
For this program you will get some practice using the STL and it's Algorithms. 
Your program is going to be very similar to the main from program 4 with some small changes. 
Note: in this program you will be using the C++ string class, not your MYString

Program Requirements: {reading and writing to files NEEDS to be done with stream iterator adapters......
and yes, when you are done with the file variables, you should close them}

You will need a couple new things for the program

A function that can be used with the transform algorithm.  
This function will take a string argument and build a new string without punctuation except single quotes ( ' ):

string punctRemover(const string& strIn); // function prototype

Example of using/testing punctRemover:
string str("h*\e&l)\"l#o*");
str = punctRemover(str);
cout << "string: " << str << "\n\n";  // would print out hello

Note: string also has iterators and begin( ) and end( ) functions and it also has a push_back( char ch) function.  
So you can use the STL's Algorithms with strings or for each loops from 131. Not required, but may be useful.  
Use whatever makes it easiest for you.

A Binary Predicate Functor* called AscDictSort (which stands for Ascending Dictionary Sort: the normal sort found in a dictionary) 
to do string comparisons so we can sort correctly strings that are both upper and lower case for example using it apple < Ask would be true.  
If this was an ASCI comparison (the normal string < ), then this would be false. 
This functor will be used by your set container to do the sorting. 
Your AscDictSort should ignore case (whether a letter is upper case or lower case should not effect it's position). 
So with your functor "The", "the" and "thE" would be considered the same word, 
and so whichever word is encountered first would be added to the set and any of the others would not be added.   
(*Remember: Binary Predicate Functor is a functor that take two string parameters and returns a bool)

Programming Note: in writing this program, I noticed that for the AscDictSort's operator ( ) function must be made a const function like this:

class AscDictSort {
 public:
 bool operator () (const string& str1, const string& str2) const { }
};

Set has an erase member function that you can use to remove a string from the set.

Remember cctype library has many helper functions {Link to cctype referenceLinks to an external site.}

Your Main should do this

-create 4 set<string, AscDictSort> objects ( set1, set2, modSet1, modSet2 ). 
Note: modSet stands for modified set. 
AscDictSort is the sorting functor that you wrote. 
The name is short for Ascending Dictionary Sort

-read all of the data from infile1.txt into set1 using the transform function. 
In the transform call, you need to use your punctRemover function 
that will make a new copy of the input string that will not have any punctuation other than ' .

-read all of the data from file2 and transform it as above before inserting it into set2

-cout the size of the 4 sets with explaining text (what size goes with which set)
-modSet1 = set1
-modSet2 = set2
-cout the size of the 4 sets with explaining text

-remove from modSet1 all of the strings from set2 (using the set's erase member function)
-remove from modSet2 all of the strings from set1
-cout the size of the 4 sets with explaining text

-output modSet1 to outfile1.txt with a space between each string
-output modSet2 to outfile2.txt with a space between each string

Files: The input files, infile1.txt and infile2.txt can be downloaded from the Files section under Course Resources/P8 Using the STL.

Additional Note: if you compare lower-case versions of the strings, as you should be, you will get the following results, 
when you are reading from infile1.txt, your set1 variable should contain 1354 strings, and set2 should include 967 words

Header files I used during the writing of the lectures (note: you shouldn't need all of these for your program):

#include <iostream>
#include <algorithm>
#include <set>
#include <string>
#include <iterator>
#include <fstream>


This program is short but has new concepts so don't wait until the last night.

Turn in: Submit a pdf of your code and output, (main, with program header. 
For the output, you need to get the information from the screen, and the text that is written to outfile2.txt 
(you do not need to print outfile1.txt)....outfile2 will be shorter than outfile1.

Ways to lose points:

if your file does not contain the program header with a program description 
and short function descriptions to accompany the function prototypes(for functions used with main).
your .h file should have a class description about what the class does
your code should also be consistently indented as talked about in class, and shown in the book
you can not use global variables unless it is a const
you should use good variable names (descriptive, and start with lower case letter )
proper placement of { and } ( a } should not be placed at the end of a line)
no staple to keep your papers together (folding a corner or using a paper clip are not good enough)
Comments: Comments are a way of documenting a program (explaining who did what and how). 
All programs for the rest of the course are required to have the following header 
documentation and inline documentation to explain any tricky pieces of code.

// File Name: Actual name of file (like assign4.cpp)
// Author: Your Name
// Assignment: #
// Description: Short description of the program (at least a couple sentences - also you should
// say where the input data come from, what information is output,
// and is the outputted data sent to the screen or a file).
// #include <iostream> .......the rest of the program

*/
