#ifndef TREEMULTIMAP_INCLUDED
#define TREEMULTIMAP_INCLUDED

#include <vector>

// TODO delete after
#include <iostream>
using namespace std;

// template <typename KeyType, typename ValueType>
template <typename KeyType, typename ValueType>
class TreeMultimap
{
    private:
        struct Node{

            KeyType m_key;
            std::vector<ValueType> m_value;

            Node *m_left;
            Node *m_right;
                        
            Node(const KeyType& key, const ValueType& value)
            {
                m_left = nullptr;
                m_right = nullptr;
                m_key = key;
                m_value.push_back(value);
            }
        };
        
    public:
        class Iterator
        {
          public:
            Iterator()
            {
                m_it = nullptr;
                m_index = 0;
            }
            Iterator(Node *curr)
            {
                m_it = curr;
                m_index = 0;
            }
            ValueType& get_value() const
            {
                return m_it->m_value[m_index];
            }

            bool is_valid() const
            {
                if( m_it == nullptr || m_index == m_it->m_value.size() )
                {
                    return false;
                }
                return true;
            }

            void advance()
            {
                if(m_index == m_it->m_value.size())
                {
                    m_index = 0;
                    return;
                }
                else
                {
                    m_index++;
                    return;
                }
            }

          private:
                Node *m_it;
                int m_index;
            
        };

    TreeMultimap()
    {
        m_root = nullptr;
    }

    ~TreeMultimap()
    {
        freeTheTree(m_root);
    }

    void insert(const KeyType& key, const ValueType& value)
    {
        // tree is empty, allocate new node and have m_root point to the new ode
        if(m_root == nullptr)
        {
           m_root = new Node(key, value);
           return;
        }
        Node *curr = m_root;
        
        for(;;)
        {
            // if the key already exists, append the value to the vector assosiated with the key
            if(key == curr->m_key)
            {
                curr->m_value.push_back(value);
                return;
            }
            // if the key is less than the current node's key
            if(key < curr->m_key)
            {
                // if there is a left child go left
                if(curr->m_left != nullptr)
                {
                    curr = curr->m_left;
                }
                else // otherwise allocate a new node and set the current node's left pointer to point to it
                {
                    curr->m_left = new Node(key, value);
                    return;
                }
            }
            else if(key > curr->m_key) // if the key is greater than the current node's key
            {
                // if there is a right child go right
                if(curr->m_right != nullptr)
                {
                    curr = curr->m_right;
                }
                else // otherwise allocate a new node and set the ucrrent node's right pointer to point to it
                {
                    curr->m_right = new Node(key, value);
                    return;
                }
            }
        }
    }

    Iterator find(const KeyType& key) const
    {
        Node* curr = m_root;
        
        while(curr != nullptr)
        {   // if the current key equals the key we want to find, we return the iterator pointing to that key
            if(key == curr->m_key)
            {
                Iterator validIt(curr);
                return validIt;
            }
            else if(key < curr->m_key) // if it's less than, move down to the left
            {
                curr = curr->m_left;
            }
            else // if it's greater than, move down to the right
            {
                curr = curr->m_right;
            }
        }
        Iterator inValidIt; // calls default constructor for iterator where m_it = nullptr, no matching key found
        return inValidIt;
    }
    

    private:

        void freeTheTree(Node *curr)
        {
            // if empty, return
            if(curr == nullptr)
            {
                return;
            }
            // delete nodes in left sub tree
            freeTheTree(curr->m_left);
            // delete nodes in right sub tree
            freeTheTree(curr->m_right);
            // free the current node
        
            delete curr;
        }
    
        Node *m_root;
};

#endif // TREEMULTIMAP_INCLUDED



