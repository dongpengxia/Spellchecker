/*
 *  DictionaryHTable.h
 *
 *  Hashtable Spellchecker
 *
 *  11/29/2016
 *  Dongpeng Xia
 */

#ifndef DictionaryHTable_h
#define DictionaryHTable_h

#include "DictionaryLL.h"

using std::string;





/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                                                                        **
 **                  class DictHTable declaration                          **
 **                                                                        **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/

class DictHTable
{
    friend ostream& operator<<(ostream&, const DictHTable&);
    //Postcondition: The dictionary hash table is output to the stream

private:
    DictLL* wordLists;
    unsigned long tableSize;
    
public:
    DictHTable(unsigned long);
    ~DictHTable();
    void clear();
    unsigned long getHashIndex(string);
    void insert(string);
    bool searchHTable(string);
    void erase(string); //the remove function
    Node* findMostAccessed();
    
}; //END class DictHTable declaration

#endif