#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE

#include <cmath>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

/**************************************************************************//**
 * @file
 *
 * @brief this file contains the basic information for function.cpp.  It should
 * be included with function.cpp.
 *
 *****************************************************************************/
#ifndef  _OURFUNCTIONS_H
#define  _OURFUNCTIONS_H

/*!
 * @brief This is our custom linklist class that contains the custom linked
 * list functions.
 *
 * @details Our custom linked list class contains functions for inserting,
 * removing, finding, incrementing the frequency of a word, a function to check
 * if the list is empty, a function to get the max frequency for a word, a size
 * function to get the size, as well as the contruster and destructor
 * functions.
 */
class LinkList
{
    public:
         /*!
         *  @brief The constructor, initializes the class upon
         *  creation
         */
        LinkList();
        /*!
         *  @brief The destructor, cleans the class when it goes
         *  out of scope
         */
        ~LinkList();
        /*!
         *  @brief Inserts a word into the string
         *         returns true if item was inserted
         */
        bool insert( string word );
        /*!
         *  @brief Removes a word from the string
         *         returns true if item was removed
         */
        bool remove( string word );
        /*!
         *  @brief Searches for a word in the string
         *         returns true if item word is found
         */
        bool find( string word );
        /*!
         *  @brief Determines the frequency of each word within
         *            the text file
         *         returns true if frequency of item is
         *         incremented
         */
        bool incrementFrequency( string word );
        /*!
         *  @brief Determines if the string is empty
         *         returns true if the list is empty
         */
        bool isEmpty();
        /*!
         *  @brief Determines the maximum frequency of a word
         *         returns the frequency count of the most common
         *         word
         */
        int getMaxFrequency();
        /*!
         *  @brief Determines the size of the string
         *         returns size of the list
         */
        int size();
        /*!
         *  @brief Prints the formatted frequency to ostream
         *         returns Nothing
         */
        void print( ostream &out );
 
    private:

        /*!
         * @brief Holds a string, how often the string occured
         * and the pointer to the next node
         *
         */
        struct node
        {
            int frequencyCount;   /*!< holds the frequency of the word */
            string word;          /*!< holds the word read into the file */
            node *next;           /*!< holds the pointer to the next node in
                                            the list*/
        };

        node *headptr;            /*!< holds the pointer to the
                                       first node of the list*/
};

#endif