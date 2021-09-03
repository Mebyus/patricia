#include "patricia.hpp"

Patricia::Node *Patricia::search(const std::string &find_key) const
{
    Node *curr_node = root->left, *prev_node = root;

    while (curr_node->index > prev_node->index)
    {
        size_t char_index = (curr_node->index - 1) / BIT_COUNT;
        if (char_index >= find_key.size())
        {
            prev_node = curr_node;
            curr_node = curr_node->left;
            continue;
        }

        char curr_char = find_key[char_index];
        int offset = BIT_COUNT - 1 - ((curr_node->index - 1) % BIT_COUNT);
        char curr_bit = (curr_char >> offset) & 1;

        prev_node = curr_node;
        if (curr_bit == 1)
        {
            curr_node = curr_node->right;
        }
        else
        {
            curr_node = curr_node->left;
        }
    }

    return curr_node;
}

void Patricia::set(const std::string &key, int value)
{
    if (root == nullptr)
    {
        root = new Node(key, value, 0);
        root->left = root;
        return;
    }

    Node *found_node = search(key);
    if (found_node->key == key)
    {
        found_node->value = value;
        return;
    }

    size_t char_index = 0;
    while (true)
    {
        char found_char = 0;
        if (char_index < found_node->key.size())
        {
            found_char = found_node->key[char_index];
        }

        char input_char = 0;
        if (char_index < key.size())
        {
            input_char = key[char_index];
        }

        for (size_t i = 0; i < BIT_COUNT; i++)
        {
            int offset = BIT_COUNT - 1 - i;
            char found_bit = (found_char >> offset) & 1;
            char input_bit = (input_char >> offset) & 1;
            if (found_bit != input_bit)
            {
                insert(key, value, char_index * BIT_COUNT + i + 1);
                return;
            }
        }
        char_index++;
    }
}

void Patricia::insert(const std::string &key, const int &value, const size_t &index)
{
    Node *curr_node = root->left, *prev_node = root;

    while (curr_node->index > prev_node->index && curr_node->index <= index)
    {
        size_t char_index = (curr_node->index - 1) / BIT_COUNT;
        if (char_index >= key.size())
        {
            prev_node = curr_node;
            curr_node = curr_node->left;
            continue;
        }

        char curr_char = key[char_index];
        int offset = BIT_COUNT - 1 - ((curr_node->index - 1) % BIT_COUNT);
        char curr_bit = (curr_char >> offset) & 1;

        prev_node = curr_node;
        if (curr_bit == 1)
        {
            curr_node = curr_node->right;
        }
        else
        {
            curr_node = curr_node->left;
        }
    }
    char char_from_key = key[(index - 1) / BIT_COUNT];
    int offset = BIT_COUNT - 1 - (index - 1) % BIT_COUNT;
    char bit = (char_from_key >> offset) & 1;
    Node *node = new Node(key, value, index);

    if (prev_node->left == curr_node)
    {
        prev_node->left = node;
    }
    else
    {
        prev_node->right = node;
    }

    if (bit == 1)
    {
        node->right = node;
        node->left = curr_node;
    }
    else
    {
        node->left = node;
        node->right = curr_node;
    }
}

std::pair<int, bool> Patricia::get(const std::string &key)
{
    if (root == nullptr)
    {
        return {0, false};
    }

    Node *found_node = search(key);
    if (found_node->key == key)
    {
        return {found_node->value, true};
    }

    return {0, false};
}
