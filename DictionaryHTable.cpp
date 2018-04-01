/*
 *  DictionaryHTable.cpp
 *
 *  Hashtable Spellchecker
 *
 *  11/29/2016
 *  Dongpeng Xia
 */

#include <iostream>
#include <string>
#include "DictionaryLL.h"
#include "DictionaryHTable.h"

using std::string;


/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                                                                        **
 **                  class DictHTable implementation                       **
 **                                                                        **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/

/****************************************************************************
 *       DictHTable class overloaded stream insertion operator              *
 ****************************************************************************/

ostream& operator<<(ostream &os, const DictHTable &hTable)
{
    for(unsigned long i = 0; i < hTable.tableSize; i++)
    {
        os << hTable.wordLists[i] << "\n";
    }
    
    return os;
    
} //END overloaded stream insertion operator for DictHTable class



/****************************************************************************
 *              DictHTable class constructor with parameters                *
 ****************************************************************************/

DictHTable::DictHTable(unsigned long m)
{
    wordLists = new DictLL[m]();
    tableSize = m;
    
} //END constructor with parameters for DictHTable class



/****************************************************************************
 *                       DictHTable class destructor                        *
 ****************************************************************************/

DictHTable::~DictHTable()
{
    clear();
    
} //END destructor for DictHTable class



/****************************************************************************
 *                  DictHTable class member function clear                  *
 ****************************************************************************/

void DictHTable::clear()
{
    delete[] wordLists;
    tableSize = 0;
    
} //END DictHTable member function clear()



/****************************************************************************
 *               DictHTable class member function getHashIndex              *
 ****************************************************************************/

unsigned long DictHTable::getHashIndex(string str)
{
    unsigned long hashLoc = 1;
    unsigned long numChars = str.length();
    for(int i = 0; i < numChars; i++)
    {
        hashLoc = hashLoc * 37 + str[i]; //use horner's method
    }
    
    hashLoc = hashLoc % tableSize;
    
    return hashLoc;
    
} //END DictHTable member function getHashIndex



/****************************************************************************
 *               DictHTable class member function insert                    *
 ****************************************************************************/

void DictHTable::insert(string str)
{
    unsigned long pos = getHashIndex(str);
    if (wordLists[pos].find(str))
    {
        //repeat, do nothing
    }
    else
    {
        wordLists[pos].push_back(str, 0);
    }
    
} //END DictHTable member function insert



/****************************************************************************
 *             DictHTable class member function searchHTable                *
 ****************************************************************************/

bool DictHTable::searchHTable(string searchStr)
{
    return wordLists[getHashIndex(searchStr)].seqSearch(searchStr);
    
} //END DictHTable member function searchHTable



/****************************************************************************
 *                DictHTable class member function erase                    *
 ****************************************************************************/

void DictHTable::erase(string removeStr)
{
    wordLists[getHashIndex(removeStr)].remove(removeStr);
    
} //END DictHTable member function erase



/****************************************************************************
 *           DictHTable class member function findMostAccessed              *
 ****************************************************************************/

Node* DictHTable::findMostAccessed()
{
    Node* maxNode = new Node();
    Node* current;
    for(unsigned long i = 0; i < tableSize; i++)
    {
        current = wordLists[i].mostPopularWord();
    
        if(current && (current->findCount > maxNode->findCount))
        {
            maxNode = current;
        }
    }
    
    return maxNode;
    
} //END DictHTable member function findMostAccessed