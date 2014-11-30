#ifndef HASHLIST_H_
#define HASHLIST_H_

#include <string>

class HashList {
  public:
    HashList();
    ~HashList();

    //const member functions
    int hashCount() const;
    int showHash(std::string) const;
    int getTableSize() const;

    //mutable functions
    bool find(const std::string);
    bool insert(const std::string);
    bool remove(const std::string);
  private:
    int hash(const std::string) const;
    void rehash();

    std::string *d_hashtbl;
};

#endif
