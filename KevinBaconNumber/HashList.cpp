#include "HashList.h"
#include <iostream>
#include <string>
#include <cstdlib>

HashList::HashList(int tblsize):
d_tblcount(0)
{
    //set min allowed hash table start size
    if(tblsize < 200)
        tblsize = 200;
    d_tblsize = tblsize;
    //create hash table
    d_hashtbl = new std::string[tblsize];
}

HashList::~HashList()
{
    delete [] d_hashtbl;
}

int HashList::hashCount() const
{
    return d_tblcount;
}

int HashList::showHash(std::string hash_test) const
{
    return hash(hash_test);
}

int HashList::getTableSize() const
{
    return d_tblsize;
}

int HashList::find(const std::string key)
{
    int hloc = hash(key);
    for(int i = 0; i < d_tblsize; i++) {
        if(d_hashtbl[hloc] == key)
            return hloc;
        hloc++;
        if(hloc >= d_tblsize)
            hloc = 0;
    }
    return false;
}

bool HashList::insert(const std::string key)
{
    if((float)d_tblcount / (float)d_tblsize > d_loadfactor)
        rehash();
    
    int hloc = hash(key);

    if(d_hashtbl[hloc] == "") {
        d_hashtbl[hloc] = key;
        d_tblcount++;
        return true;
    } else {
        while(true) {
            //use linear probing
            hloc++;

            if(hloc >= d_tblsize)
                hloc = 0;

            if(d_hashtbl[hloc] == "") {
                d_hashtbl[hloc] = key;
                return true;
            }
        }
    }
    return false;
}

bool HashList::remove(const std::string key)
{
    int hloc = hash(key);
    for(int i = 0; i < d_tblsize; i++) {
        if(d_hashtbl[hloc] == key) {
            d_hashtbl[hloc] = "";
            d_tblcount--;
            return true;
        }
        hloc++;
        if(hloc >= d_tblsize)
            hloc = 0;
    }
    return false;
}

int HashList::hash(const std::string key) const
{
    int seed = 131;
    unsigned long hash = 0;
    for(int i = 0; i < key.length(); i++) {
        hash = (hash * seed) + key[i];
    }
    return hash % d_tblsize;
}

void HashList::rehash()
{
    std::string oldentries[d_tblcount];
    for(int j = 0, i = 0; i < d_tblsize; i++) {
        if(d_hashtbl[i] != "") {
            oldentries[j] = d_hashtbl[i];
            j++;
        }
    }

    delete [] d_hashtbl;
    d_tblsize *= 2;
    d_hashtbl = new std::string[d_tblsize];
    d_tblcount = 0;

    for(int i = 0; i < sizeof(oldentries) / sizeof(oldentries[0]); i++) {
        insert(oldentries[i]);
    }
}
