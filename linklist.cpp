/**************************************************************************//**
 * @file
 *
 * @brief This file contains the function definitions for the LinkList class
 * and should be included with prog2.cpp and linklist.cpp
 *****************************************************************************/
#include "linklist.h"


/**************************************************************************//**
 * @author Andrew Fagrey
 *
 * @par Description: This function is the constructor function for the linked
 * list class.
 *
 * @returns none
 *****************************************************************************/
LinkList::LinkList()
{
	// initialize headptr to nullptr
	headptr = nullptr;
}


/**************************************************************************//**
 * @author Matthew Babb
 *
 * @par Description: This is a custom destructor for the link list. A previous
 * and current pointer are created. These pointers then walk through the
 * linked list, deleting nodes until the current pointer is pointing to
 * null memory.
 *
 * @returns There are no valid return types.
 *
 *****************************************************************************/
LinkList::~LinkList()
{
	if (headptr != nullptr)
	{
		node *prev = headptr;        
		
		//Declaration of prev and curr pointers.

		node *curr = headptr;
		curr = curr->next;
		do                            
		
		/*Loop deletes current node and moves 
		the nodes down the list, continuing to delete 
		them while the node does not point to null memory.*/

		{ 
			prev = curr; 
			curr = curr->next;
			delete(prev);
		}
		while(curr != nullptr);
	}
	delete headptr;                    
	
	//Removes the last remaining node.

}


/**************************************************************************//**
 * @author Bryon Glass
 *
 * @par Description: This function will take a word and put it into a
 * linked list. It will put it into the link list by the string numerical
 * order, with lower numbers first.  It will also set the frequencyCounter
 * equal to 1.  If the same word already exist it will add a second one to the
 * list
 *
 * @param[in] word - A word that is to be inserted into the list
 *
 * @returns true If the word got inserted into the list
 * @returns false If the word did not get inserted into the list
 *****************************************************************************/
bool LinkList::insert( string word )
{
	//Create the new node that will be added
	node* adding = new (nothrow) node;

	//Makes sure it was able to get the node
	if(adding == nullptr){
		return false;
	}
	adding->word = word;
	adding->frequencyCount = 1;
	//Current and previous used in inserting the node
	node *prev;
	node *curr;

	//If headptr is null, the new node is inserted into an empty list
	if(headptr == nullptr)
	{
		headptr = adding;
		headptr->next = nullptr;
		return true;
	}

	//Assign positions to current and previous
	curr = headptr;
	prev = curr;

	//Adds it to the front of the list if it comes first alphabetically.
	if( adding->word.compare(curr->word) <= 0)
	{
			adding->next = curr;
			headptr = adding;
			return true;
	}

	while ( curr != nullptr )
	{
		/*Compares words, finding the correct place to insert, then ensures
		the rest of the list*/
		if( adding->word.compare(curr->word) <= 0)
		{
			//
			adding->next = curr;
			prev->next = adding;
			return true;
		}
		//moves to the next node in the list
		prev = curr;
		curr = curr->next;
	}

	//Adds to the end of the list, with the last node pointing to null
	prev->next = adding;
	adding->next = nullptr;
	return true;
}


/**************************************************************************//**
 * @author Matthew Babb
 *
 * @par Description: The LinkList::remove function is responsible for removing
 * a word from the linked list while keeping the list intact. It will call the
 * find function to determine if the word is in the list. If not, the remove
 * function will return false. When it has been determined that the word is in
 * the list it will walk through and find its location, remove it, and patch
 * the remainder of the list together.
 *
 * @param[in] word - a string, the word which is to be removed
 *
 * @returns false The word is not in the list.
 * @returns true  The word was found and removed from the linked list.
 *****************************************************************************/
bool LinkList::remove(string word)
{
	node *temp;                                
	
	//Declaration of future nodes

	node *curr = headptr;
	node *prev = headptr;
	if (LinkList::find(word) == false)        
	{

	//If the word is not in the list, return false and exit function.

		return false;
	}
	if (headptr->word == word)                
		
		//Determine if the word is in the headpointer. 

	{
	   
		if (headptr->next == nullptr)

			/*If it is, determine if it is the 
			only word in the list and properly remove it.*/

		{ 
			delete headptr;
			headptr = nullptr;
			return true;
		}
		if (headptr->next != nullptr)        
			
			/*If it is not the only word in the list, 
			ensure the remainder of the list is not lost.*/

		{ 

			temp = headptr;
			headptr = headptr->next;
			delete temp;
			return true;
		}
	}
	while (curr->word != word)                
		
		/*While loop walks through list 
		finding the node with the desired word.*/

	{        
		prev = curr;    
		curr = curr->next;
	}
	if (curr->next != nullptr)                
		
		/*If the word is found in the middle 
		of the list, remove it and maintain the rest of the list.*/

	{ 
		prev->next = curr->next;
		delete curr;
		return true;
	}
	if (curr->next == nullptr)                
		
		/*If the word is found at the end of the list, 
		remove it and set the previous nodes next pointer 
		to null, signifying the end of the list.*/

	{ 
		prev->next = nullptr; 
		delete curr;
		return true;
	}

	return false;
}


/**************************************************************************//**
 * @author Andrew Fagrey
 *
 * @par Description: This is the find funciton. Given a word, it goes through
 * the linked list looking for the word. If the word is found, the function
 * returns true. If the word is not found, it returns false.
 *
 * Tested by: Bryon G.
 *
 * @param[in] word - a c++ string that contains a single word to search for
 *
 * @returns true Word was found
 * @returns false Word was not found
 *****************************************************************************/
bool LinkList::find( string word )
{
	// if headptr is equal to nullptr, the list is empty
	if( headptr == nullptr )
	{
		return false;
	}

	// declare temp and set equal to headptr
	node *temp;
	temp = headptr;

	// search through the list while temp doesn't equal nullptr
	while( temp != nullptr )
	{
		// if word is found, return true
		if( temp->word == word )
			return true;

		// advance temp if not found
		temp = temp->next;
	}

	// if at end of list and word not found, return false
	return false;
}


/**************************************************************************//**
 * @author Matthew De Young
 *
 * @par Description: Upon recieving a word to have it's frequency incremented,
 *                   the existance of that word is initially checked. Once the
 *                   word is confirmed to exist within the list, a temporary
 *                   node is stepped through the list, checking for the word.
 *                   upon finding the word it's frequency is incremented and
 *                   true is returned for incrementing success.
 *
 * @param[in] word - the word to have it's frequency incremented.
 *
 * @returns true if incrementing succeeded
 * @returns false if it did not increment
 *****************************************************************************/
bool LinkList::incrementFrequency( string word )
{
	node *temp;
	temp = headptr;
	if( find(word) )
	{
		while( temp != nullptr )
		{
			if( temp->word == word )
			{
				temp->frequencyCount++;
				return true;
			}
			else
			{
				temp = temp->next;
			}

		}
	}
	return false;
}


/**************************************************************************//**
 * @author Bryon Glass
 *
 * @par Description: A function used to tell if the link list is empty
 *
 * @returns true if the list is empty
 * @returns false if there is something in the list
 *****************************************************************************/
bool LinkList::isEmpty()
{
	//If headptr equall nullptr then the list is empty
	if( headptr == nullptr )
	{
		return true;
	}
	//return false because the list is not empty.
	return false;
}


/**************************************************************************//**
 * @author Matthew Babb
 *
 * @par Description: The LinkList::getMaxFrequency function is used to find the
 * number of times the most used word appears in a word document. The function
 * checks for an empty list, and returns zero. If the list is not empty, a
 * single pointer is created which then walks through the linked list,
 * comparing the frequency of the node to the current maximum frequency. When
 * the node reaches the end of the list, the maximum value is returned.
 *
 * @returns 0 if list is empty.
 * @returns freq - An integer value which is the amount of times the most used
 * word occurs.
 *****************************************************************************/
int LinkList::getMaxFrequency()
{
	if (headptr->frequencyCount == 0)       
		
		//Checks for an empty list, where frequnce returned is zero.

	{ 
		return 0;
	}
	node *curr = headptr->next;
	int freq = headptr->frequencyCount;        
	
	//Integer value, stores the max frequency for comparing.

	do  
	{
		if (curr->frequencyCount > freq)    
			
			/*Do...While loop compares the current node to the 
			current max frequency until it reaches the end of the list.*/

		{  
			freq = curr->frequencyCount;
		} 
		curr = curr->next;
	}
	while(curr != nullptr);                    
	
	//Maximum frequency found in the list is returned to the program.

	return freq;                          
}  


/**************************************************************************//**
 * @author Bryon Glass
 *
 * @par Description: This function takes a link list and loops through it
 * looking for nullptr, counting how many nodes are in the list
 *
 * @returns totalSize -    The size of the link list
 *****************************************************************************/
int LinkList::size()
{
	//creates a temporary node to store the node being worked on
	node *start;

	//the character used to store the size of the linked list
	int totalSize = 0;
   
	start = headptr;
   
	//loops through the link list looking for nullptr adding up how many nodes
	//there are
	while ( start != nullptr )
	{
		totalSize++;
		start = start->next;
	}

	//returns how many nodes there are
	return totalSize;
}


/**************************************************************************//**
 * @author Matthew De Young
 *
 * @par Description: Prints output to given ostream, beginning with a formatted
 *                   frequency header displaying the maximum frequency of the 
 *                   words and followed by printing those words themselves.
 *                   Those words are then removed from the list, and the 
 *                   process repeats until the list is empty and all words
 *                   have been printed.
 *
 * @param[in] out to determine if user desires output to the screen
 *            or to a file.
 *
 * @returns none
 *****************************************************************************/
void LinkList::print( ostream &out )
{
	node *temp;
	bool isFirstFreq = true;
	bool isFirstWord = true;
	int i = 0;
	int freq = 0;
	//initializing the temporary node to the headpointer node
	temp = headptr;
	//storing the maximum frequency
	freq = getMaxFrequency();
	//for loop, stepping from the maximum frequency to the frequency of 1
	for( i = freq; i > 0; i--)
	{
		//stepping through the list without overstepping the bounds
		 while( temp != nullptr )
		 {
			 //compares current temporary node's word frequency to the 
			 //current maximum frequency
			 if( temp->frequencyCount == i )
			 {
				 //if statement, testing if the word with the current frequency
				 //is the first word with that frequency. If so a header
				 //with this frequency is printed
				 if( isFirstFreq )
				 {
					 out << "================================================"
						 << "===============================" << endl;
					 out << setw(10) << "      Frequency Count: "<< i <<endl;
					 out << "================================================"
						 << "===============================" << endl;
					 isFirstFreq = false;
				 }
				 //if else statements, toggling the isFirstWord bool to output
				 //to either of the first or second column
				 if( isFirstWord )
				 {
					out << setw(20) << left << temp->word;
					isFirstWord = false;
				 }
				 else
				 {
					out << temp->word << endl;;
					isFirstWord = true;
				 }
			 }
			 //moves the temporary node to the next node in the list
			 temp = temp->next;
			 //if statement for the output of a new line, preventing the header
			 //from being printed onto the end of a word
			 if( !isFirstWord && temp == nullptr && isFirstFreq == false )
			 {
				 out<<endl;
			 }
		 }
		 isFirstFreq = true;
		 //reinitializes the temporary node to headpointer, so that the list
		 //may be searched through for each potential frequency
		 temp = headptr;
	}
}