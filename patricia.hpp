#ifndef PATRICIA_H
#define PATRICIA_H

#include <string>
#include <utility>

const int BIT_COUNT = 5;

class Patricia
{
private:
    struct Node;
    Node *root = nullptr;

    Node *search(const std::string &find_key) const;
    void insert(const std::string &key, const int &value, const size_t &index);

public:
    void set(const std::string &key, int value);
    std::pair<int, bool> get(const std::string &key);
};

struct Patricia::Node
{
    std::string key;
    int value;
    size_t index;
    Node *right, *left;

    Node(const std::string &key, const int &value, const int &index) : key(key), value(value), index(index), left(nullptr), right(nullptr) {}
    ~Node() {}
};

#endif
