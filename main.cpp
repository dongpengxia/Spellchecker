/*
 *  main.cpp
 *
 *  Hashtable Spellchecker
 *
 *  11/29/2016
 *  Dongpeng Xia
 */


#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cmath>
#include <stdexcept>
#include "DictionaryHTable.h"

using std::string;
using std::stringstream;
using std::fstream;
using std::cout;
using std::endl;
using std::bad_alloc;

//exception classes
class fileOpenError{};
class tooFewArguments{};

//function lowerAlphaOnly accepts a string and returns it with only lowercase alphabet letters
string lowerAlphaOnly(string);

//loadDictionaryHTable reads input dictionary file into a dictionary Hash Table
void loadDictionaryHTable(string, DictHTable&);

//function spellCheckInputFileHTable spellchecks an input file, returns misspelled count
unsigned long spellCheckInputFileHTable(string, DictHTable&);

//function removeFileItemsFromDictHTable removes items from removal file from dictionary Hash Table
void removeFileItemsFromDictHTable(string, DictHTable&);

//function isPrime returns a boolean indicating if an integer is a prime number (assume n != 2)
bool isPrime(unsigned long);

//function getNextPrime returns the next prime greater than or equal to an integer (assume num > 2)
unsigned long getNextPrime(unsigned long);



int main(int argc, const char * argv[])
{
    try
    {
        if(argc > 3)
        {
            string inputFile = string(argv[1]);        //inputFile passed in
            string dictFile = string(argv[2]);         //dictFile passed in
            string removalFile = string(argv[3]);      //removalFile passed in
        
            unsigned long numMispelled = 0;
            clock_t timeBegin, timeEnd;
            double spellCheckTime = 0.0;
            unsigned long tableSize = 500009; //prime number
		
	    //Hash Table Spell Checking
            DictHTable table1(tableSize);
            loadDictionaryHTable(dictFile, table1);
        
            timeBegin = clock();
            numMispelled = spellCheckInputFileHTable(inputFile, table1);
            timeEnd = clock();
            spellCheckTime = (double)(timeEnd - timeBegin)/CLOCKS_PER_SEC;
            Node *mostFrequent = table1.findMostAccessed();
        
            cout << "HASH TABLE SPELLCHECKER:" << endl;
            cout << "Number of Misspelled Words: " << numMispelled << endl;
            cout << "Spellchecking runtime: " << spellCheckTime << endl;
            cout << "Most frequently accessed word: " << mostFrequent->word << endl;
            cout << "Number of times word was accessed: " << mostFrequent->findCount << endl;
            cout << endl;
		
            //Hash Table Removal Then Spell Checking
            DictHTable table2(tableSize);
            loadDictionaryHTable(dictFile, table2);
            removeFileItemsFromDictHTable(removalFile, table2);
        
            timeBegin = clock();
            numMispelled = spellCheckInputFileHTable(inputFile, table2);
            timeEnd = clock();
            spellCheckTime = (double)(timeEnd - timeBegin)/CLOCKS_PER_SEC;
            mostFrequent = table2.findMostAccessed();
        
            cout << "HASH TABLE SPELLCHECKER (AFTER WORD REMOVALS):" << endl;
            cout << "Number of Misspelled Words: " << numMispelled << endl;
            cout << "Spellchecking runtime: " << spellCheckTime << endl;
            cout << "Most frequently accessed word: " << mostFrequent->word << endl;
            cout << "Number of times word was accessed: " << mostFrequent->findCount << endl;
            cout << endl;
        }
        else
        {
            //error: not enough arguments
            tooFewArguments error;
            throw error;
        }
         
    }//END try block
    catch(tooFewArguments error)
    {
        cout << "ERROR: Not enough arguments. Need file names and paths." << endl;
    }
    catch(fileOpenError error)
    {
        cout << "ERROR: File failed to open." << endl;
    }
    catch(bad_alloc error)
    {
        cout << "ERROR: Failed to allocate dynamic memory" << endl;
    }
    catch( ... )
    {
        cout << "ERROR: UNKNOWN ERROR CAUGHT IN MAIN" << endl;
        
    } //END catch all block
    
    return 0;
    
}//END function main()



//function lowerAlphaOnly accepts a string and returns it with only lowercase alphabet letters
string lowerAlphaOnly(string str)
{
    string result = "";
    char c;
    
    for(int index = 0; index < str.length(); index++)
    {
        c = str[index];
        if(isalpha(c))
        {
            result = result + char(tolower(c));
        }
    }
    
    return result;
    
} //end lowerAlphaOnly function



//loadDictionaryHTable reads input dictionary file into a dictionary Hash Table
void loadDictionaryHTable(string fileNameAndPath, DictHTable& dictionary)
{
    try
    {
        fstream inFileStream;
        
        //Open file name and path
        inFileStream.open(fileNameAndPath.c_str());
        
        //If the input data file failed to open
        if(!inFileStream)
        {
            fileOpenError fileError;
            throw fileError;
        }
        else
        {
            //fileNameAndPath opened correctly
            string str;
            
            while(inFileStream >> str)
            {
                str = lowerAlphaOnly(str);
                if(str != "")
                {
                    dictionary.insert(str);
                }
            }
        }
        
        inFileStream.close();
    }
    catch(fileOpenError error)
    {
        throw;
    }
    catch( ... )
    {
        throw;
    }

} //end loadDictionaryHTable function



//function spellCheckInputFileHTable spellchecks an input file, returns misspelled count
unsigned long spellCheckInputFileHTable(string fileNameAndPath, DictHTable& dictionary)
{
    try
    {
        unsigned long misspelledCount = 0;
        
        fstream inFileStream;
        
        //Open file name and path
        inFileStream.open(fileNameAndPath.c_str());
        
        //If the input data file failed to open
        if(!inFileStream)
        {
            fileOpenError fileError;
            throw fileError;
        }
        else
        {
            //fileNameAndPath opened correctly
            string str;
            
            while(inFileStream >> str)
            {
                str = lowerAlphaOnly(str);
                if(str != "")
                {
                    if(dictionary.searchHTable(str))
                    {
                        //str is in the dictionary
                    }
                    else
                    {
                        //str is not in the dictionary
                        misspelledCount++;
                    }
                }
            }
        }
        inFileStream.close();
        
        return misspelledCount;
    }
    catch(fileOpenError error)
    {
        throw;
    }
    catch( ... )
    {
        throw;
    }

} //end spellCheckInputFileHTable



//function removeFileItemsFromDictHTable removes items from removal file from dictionary Hash Table
void removeFileItemsFromDictHTable(string fileNameAndPath, DictHTable& dictionary)
{
    try
    {
        fstream inFileStream;
        
        //Open file name and path
        inFileStream.open(fileNameAndPath.c_str());
        
        //If the input data file failed to open
        if(!inFileStream)
        {
            fileOpenError fileError;
            throw fileError;
        }
        else
        {
            //fileNameAndPath opened correctly
            string str;
            
            while(inFileStream >> str)
            {
                str = lowerAlphaOnly(str);
                if(str != "")
                {
                    dictionary.erase(str);
                }
            }
        }
        inFileStream.close();
    }
    catch(fileOpenError error)
    {
        throw;
    }
    catch( ... )
    {
        throw;
    }
    
} //end removeFileItemsFromDictHTable



//function getNextPrime returns the next prime greater than or equal to an integer (assume num > 2)
unsigned long getNextPrime(unsigned long num)
{
    if(num % 2 == 0)
    {
        //make num an odd integer
        num += 1;
    }
    while(!isPrime(num))
    {
        //keep adding 2 to num (an odd), until a prime number is found
        num += 2;
    }
    return num;
    
} //end getNextPrime



//function isPrime returns a boolean indicating if an integer is a prime number (assume n > 2)
bool isPrime(unsigned long n)
{
    bool prime = true;
    if(n % 2 == 0)
    {
        prime = false;
    }
    
    unsigned long divisor = 3;
    unsigned long sqrtN = sqrt(n);
    while(prime && divisor <= sqrtN)
    {
        if(n % divisor == 0)
        {
            prime = false;
        }
        divisor += 2;
    }
    return prime;
    
} //end isPrime