#ifndef PHONEHASH_H_
#define PHONEHASH_H_

#include <string>

class phoneHash {
  public:
    phoneHash();
    ~phoneHash();

    int entries() const;
    bool insert(const std::string, const std::string);
    bool remove(const std::string);

    bool readPhonebook(const std::string);
    std::string search(const std::string);
    void printPhonebook() const;
    int getTablesize() const;
    int showHash(std::string) const;
  private:
    int hash(const std::string) const;
    void rehash();
    bool verifyPhoneNumber(const std::string);
    std::string title;
    int count;
    int tableSize;
    std::string **phoneBook;
    static const double loadFactor=0.65;
    static const int initialTableSize=503;
};

#endif
