#include "phoneHash.h"
#include <string>

phoneHash::phoneHash():
title(""), count(0), tableSize(0),
phoneBook(NULL)
{
  phoneBook = new *std::string[initialTableSize];
  for(int i = 0; i < initialTableSize; i++)
    phoneBook[i] = new std::string[2];
}

phoneHash::~phoneHash()
{
  if(phoneBook != NULL) {
    for(int i = 0; i < tableSize; i++)
      delete [] phoneBook[i];
    delete [] phoneBook;
  }
}

int phoneHash::entries() const
{

}

bool phoneHash::insert(const std::string phoneNum, const std::string contact)
{
  if(phoneNum.length() > 10)
    return false;
  if((float)count/(float)tableSize > loadFactor)
    rehash();


}

bool phoneHash::remove(const std::string)
{

}

bool phoneHash::readPhonebook(const std::string)
{

}

std::string phoneHash::search(const std::string)
{

}

void phoneHash::printPhonebook(const std::string)
{

}

int phoneHash::getTablesize() const
{

}

bool phoneHash::verifyPhoneNumber(const std::string)
{

}

int phoneHash::showHash(std::string) const
{

}

int phoneHash::hash(const std::string) const
{

}

void phoneHash::rehash()
{

}
