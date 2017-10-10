/**************************************************************************//***************************************
 * @file
 *
 * @brief This is the prog3.cpp which contains the programs main function.
 *
 * @mainpage Program 3: Reverse Typoglycemia
 *
 * @section course_section Course Information
 *
 * @author Matthew Babb
 *
 * @date April 14, 2014
 *
 * @par Professor:
 *         Professor Roger Schrader
 *
 * @par Course:
 *         CSC 250 - M001 - 11:00am
 *
 * @par Location:
 *         Classroom Building - 204W
 *
 * @section program_section Program Information
 *
 * @details This program is designed to decode text written in typoglycemic 
 * format; a writting format in which the first and last letters of a word 
 * remain in place and the internal letters are aranged in a random order.
 *	The program will be ran from the command line, with an input file with the 
 * scrambled message, and a desired ouput file. A dictionary file will also be
 * included, but does not need to be specified in the command line. The 
 * dictionary will then be loaded into a linked list and used to verify an
 * unscrambled word.
 *	When a word is read in, any capitalization or ending punctuation will be 
 * preserved. The word will then run through permutations, looking for the 
 * first and last letter to be in place. When a possible combination has 
 * been found it will traverse through the linked list dictionary, looking
 * for a match. If there is a match, the corrected word will be returned and
 * the proper punctuation and capitalization will be restored. If no suitable
 * match is found, the word will be output in its origianl form, preceeded by
 * an asterisk. Words with less than three letters will not need to be 
 * permutated, and will be directly ouput.
 *
 * @section compile_section Compiling and Usage
 *
 * @par Compiling Instructions:
 *      None
 *
 * @par Usage:
   @verbatim 
   c:\> prog3.exe
   d:\> c:\bin\prog3.exe
   @endverbatim
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 *
 * @bug
 *
 * @todo
 *
 * @par Modifications and Development Timeline:
   @verbatim
   Date			Modification
   ------------	-----------------------------------------------------------
   Apr 03, 2014     Command line arguments verified, as well as opening files.
   Apr 04, 2014		Read the dictionary into the linked list.
   Apr 05, 2014		Read in the words from one file, ouput them to another, 
				preserving spacing.
   Apr 07, 2014		Handle capitals and punctuation marksl
   Apr 11, 2014		Permute the inner characters, search for dictionary match.
   Apr 12, 2014		Output the word to the file with the capital letters and 
				punctuation restored.
   Apr 13, 2014		Output original words with a star if no permutations match.
   @endverbatim
 *
 *****************************************************************************/

#include "linklist.h"

/******************************************************************************
 *                         Function Prototypes
 *****************************************************************************/
bool commandLine( int argc );
bool openDictionary(LinkList &dictionary);
bool fixTypo(char** argv, LinkList &dictionary);
char* permute ( char *solution, int *used, int n, char word[], 
			  int pos, char first, char last, LinkList &dictionary );
void preserveCap(int &caps, char word[], int &letter);
void preservePunct(int &i, int &puncTest, char &punct, char word[]);
void addStar(int caps, int letter, 
			 char word[], int puncTest, int i, char punct);
void recap (int caps, int letter, char word[]);
void rePunct (int puncTest, int i, char punct, char word[]);

 /**************************************************************************//*
 * @author Matthew Babb
 *
 * @par Description: The main function takes the parameters of argc and argv.
 * Inside are all neccessary function calls and validation. The command line
 * is validated first, then the dictionary is loaded and the fix function
 * begins its loopl
 *
 * @param[in] argc - the number of arguments from the command prompt.
 * @param[in] argv - a 2d array of characters containing the arguments.
 *
 * @returns 0 program ran successfully
 * @returns 1 program failed: command line or error with files
 *
 *****************************************************************************/
int main(int argc, char** argv)
{
	LinkList dictionary;

	if (commandLine(argc) == false)
	{
		return 1;
	}
	//validates command line for porper number of arguments

	if (openDictionary(dictionary) == false)
	{
		return 1;
	}
	//verifies the dictionary was opened and loaded

	fixTypo(argv, dictionary);
	//fixTypo function conatains all function calls needed to fix typoglycemia
	return 0;
}

 /**************************************************************************//*
 * @author Matthew Babb
 *
 * @par Description: The command line function takes the number of arguments, 
 * argc, and verifies the correct number. If there is an error, a simple usage
 * statement is output.
 *
 * @param[in] argc - the number of arguments from the command prompt.
 *
 * @returns True - program ran successfully
 * @returns False - Error in the number of arguments
 *
 *****************************************************************************/
bool commandLine( int argc )
{
	// Check if argc is equal to 3
	if( argc != 3 )
	{

		// Output error message if argc is not correct and return false
		cout << "Incorrect number of arguemnts: Must have program " 
			<< "name, an input file and an output file." << endl;

		return false;
	}

	// return true if argc is 3
	return true;
}

 /**************************************************************************//*
 * @author Matthew Babb
 *
 * @par Description: The openDictionary function is a very simple function
 * that opens a predetermined file. It reads through the file, storing each
 * word in a linked list that will be used as a dictionary.
 *
 * @param[in] dictionary - a linked list
 *
 * @returns True - Dictionary was loaded successfully
 * @returns False - an error loading the dictionary
 *
 *****************************************************************************/
bool openDictionary(LinkList &dictionary)
{
	ifstream fin;
	string word;

	//opens the dictionary input stream
	fin.open("dictionary.txt");

	if(!fin)
	{
		
		//checks for input from dictionary file
		cout << "Error Loading Dictionary" << endl;
		return false;
	}

	while(fin >> word)
	{

		//while there is valid input, insert into linked list
		dictionary.insert(word);
	}

	fin.close();
	//close input stream

	return true;

}

 /**************************************************************************//*
 * @author Matthew Babb
 *
 * @par Description: The fixTypo function holds the brunt of the operations for
 * fixing the typoglycemia. It opens the input and output file, as well as all
 * initializations for the word and the permutations. Once inside the while
 * loop several functions are called for caps and punctuation, the main
 * permutation function, and the restoring functions.
 *
 * @param[in] argv - a 2d array of characters containing the arguments.
 * @param[in] dictionary - used for checking word validity.
 *
 * @returns True - function was sucessful
 * @returns False - Error in file streams
 *
 *****************************************************************************/
bool fixTypo(char** argv, LinkList &dictionary)
{
	ifstream fin;
	ofstream fout;

	//open input and output files
	char word[40];
	
	fin.open(argv[1]);
	if(!fin)
	{

		//validate input
		cout << "Error Opening Typoglycemia File" << endl;
		return false;
	}
	fout.open(argv[2]);
	cout << "Decoding Typoglycemic File..." << endl;

	while (fin >> word)
	//loop to run through all words in document and permute them
	{
		int caps = 0, letter = 0, puncTest = 0, i = 0;
		char solution[40] = {0};
		int used[40] = {0};
		int pos = 0;
		string fixedWord;
		char punct = '\0', spacing = '\0', first = '\0', last = '\0';
		//these variables must be reset for each loop

		spacing = '\0';

		spacing = fin.peek();
		//preserves spacing
		
		preserveCap(caps, word, letter);
		preservePunct(i, puncTest, punct, word);
		//preserve any caps and punctuation

		if( i > 2 )
		//if there are more than 3 letter, run a permutation
		{
			first = word[0];
			last = word[i];
			//first and last word, used to permute
			
			fixedWord = permute ( solution, used, i+1, word, 
				pos, first, last, dictionary);
			//permutation to find a word

			if(fixedWord == word)
			{
				//if the word is not found in a dictionary, add a star
				addStar(caps, letter, word, puncTest, i, punct);
			}

			else
			{
				//copy the fixed word into the word array
				strcpy(word, fixedWord.c_str());
			}
		}

		recap(caps, letter, word);
		rePunct(puncTest, i, punct, word);
		//restore caps and punctuation

		fout << word;
		fout << spacing;
		//output word and spacing
	}

	fin.close();
	fout.close();
	//close input and output

	cout << "Completed Translating   ";
	return true;

}

 /**************************************************************************//*
 * @author Matthew Babb
 *
 * @par Description: The permute function is a normal permutations function. It
 * has parameters to check only valid possibilities. After being passed in a 
 * string, the function passes permutes for all possible words.
 *
 * @param[in] solution - holds the possible correct word
 * @param[in] used - array that holds bool values for the used letters
 * @param[in] n - the number of spots a possible letter could be
 * @param[in] word - the scrambled word to be permuted
 * @param[in] pos - the location the next permuted letter will go
 * @param[in] first - the required first character of the word
 * @param[in] last - the required last character of the word
 * @param[in] dictionary - used to check validity of a possible word
 *
 * @returns solution - a correct word that has been found in the dictionary
 * @returns word - no suitable correction was found
 *
 *****************************************************************************/
char* permute ( char *solution, int *used, int n, char word[], 
			  int pos, char first, char last, LinkList &dictionary )
{
	int i = 0;

	if( pos == n)
	// if all positions are filled
	{

		if( solution[0] == first && solution[n-1] == last )
		//if first and last letters are correct
		{

			if(dictionary.find(solution) == true)
			//if the word is found in the dictionary
			{
				//return the fixed word
				return solution;
			}
		}
	}

	for( i; i<n; i++)
		//permute through letters
	{

		if( used[i] == 0 )
		//if the letter is not used
		{

			solution[pos] = word[i];
			used[i] = 1;
			//insert the letter and call the function again

			permute( solution, used, n, word, pos+1, first, last, dictionary);
			if(dictionary.find(solution) == true)
				//used for returning correct word
				{
					return solution;
				}
			used[i] = 0;
		}
	}
	return word; 
	//if the corrected word is not found, return the original word
}

/**************************************************************************//*
 * @author Matthew Babb
 *
 * @par Description: The preserveCap function check the first letter in a
 * the word, storing a value to mark if it is capitalized.
 *
 * @param[in] caps - an integer value that represents a capital letter
 * @param[in] word - the scrambled word to be permuted
 * @param[in] letter - the integer value of the capital letter
 *
 * @returns None
 *
 *****************************************************************************/
void preserveCap(int &caps, char word[], int &letter)
{
	caps = isupper(word[0]);
		if(caps != 0)
		//if caps is flagged as a capital letter

		{

			letter = tolower(word[0]);
			word[0] = letter;
		}
		//preserves capitalization
}

/**************************************************************************//*
 * @author Matthew Babb
 *
 * @par Description: The preservePunct function checks for punctuation at the 
 * end of a word, then stores the punctuation.
 *
 * @param[in] i - used for loop through word
 * @param[in] puncTest - Value used to flag if punctuation
 * @param[in] punct - stores the punctuation
 * @param[in] word - the word to be checked
 *
 * @returns None
 *
 *****************************************************************************/
void preservePunct(int &i, int &puncTest, char &punct, char word[])
{
	while(word[i])
	//finds end of word
	{
		i++;
	}
	i--;
	

	puncTest = ispunct(word[i]);
	if( puncTest != 0)
	//if puncTest is flagged as having capitalization

	{
		punct = word[i];
		word[i] = '\0';
		i--;
	}
		//preserving punctuation
}

/**************************************************************************//*
 * @author Matthew Babb
 *
 * @par Description: The addStar function is designed to place the asterisk at 
 * the begining of an unfound word. It traverses the array, moving 
 * everything down to make room for the star. It will also re-capitalize
 * and re-punctuate the word;
 *
 * @param[in] caps - an integer value that represents a capital letter
 * @param[in] letter - the integer value of the capital letter
 * @param[in] word - the word to be checked
 * @param[in] puncTest - Value used to flag if punctuation
 * @param[in] i - used for loop through word
 * @param[in] punct - stores the punctuation
 *
 * @returns None
 *
 *****************************************************************************/
void addStar(int caps, int letter, 
			 char word[], int puncTest, int i, char punct)
{
	int j = 39;

	recap(caps, letter, word);
	//fix capital letters

	for (j; j>=0; j--)
	/*traverse backwards through the word, 
	moving everything down to make room for the star*/

	{
		word[j+1] = word[j];
	}
	word[0] = '*';
	//add star

}

/**************************************************************************//*
 * @author Matthew Babb
 *
 * @par Description: The recap function returns any capitalization to its 
 * original state.
 *
 * @param[in] caps - an integer value that represents a capital letter
 * @param[in] letter - the integer value of the capital letter
 * @param[in] word - the scrambled word to be permuted
 *
 * @returns None
 *
 *****************************************************************************/
void recap (int caps, int letter, char word[])
{
	if(caps != 0)
	//if caps has been flagged

		{
			letter = toupper(word[0]);
			word[0] = letter;
		}
		//Restores capital letter
}

/**************************************************************************//*
 * @author Matthew Babb
 *
 * @par Description: The rePunct replaces any punctuation that has earlier 
 * been detected.
 *
 * @param[in] i - used for placement of punctuation
 * @param[in] puncTest - Value used to flag if punctuation
 * @param[in] punct - stores the punctuation
 * @param[in] word - the word to be replaced
 *
 * @returns None
 *
 *****************************************************************************/
void rePunct (int puncTest, int i, char punct, char word[])
{
	if(puncTest != 0)
	//if puncTest has been flagged

		{
			i++;
			word[i] = punct;
		}
		//Restores any punctuation
}