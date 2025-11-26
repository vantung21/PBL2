#ifndef MYMAP_H
#define MYMAP_H

#include <utility>
#include <cstddef>

enum Color { RED, BLACK };

template <typename Key, typename Value>
struct RBNode {
    std::pair<const Key, Value> kv;
    Color color;
    RBNode* left;
    RBNode* right;
    RBNode* parent;

    RBNode(const Key& k, const Value& v)
        : kv(k, v), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

template <typename Key, typename Value>
class mymap {
public:
    using node_type = RBNode<Key, Value>;
    using value_type = std::pair<const Key, Value>;
    using key_type = Key;
    using mapped_type = Value;

    mymap() : root(nullptr), _size(0) {}
    ~mymap() { clear(root); root = nullptr; _size = 0; }

    void insert(const Key& key, const Value& value);
    Value* find(const Key& key) const;
    Value& operator[](const Key& key);
    Value& at(const Key& key) const;

    bool empty() const { return _size == 0; }
    std::size_t size() const { return _size; }

    // iterator: bidirectional, in-order
    class iterator {
        friend class mymap;
    public:
        iterator(node_type* n = nullptr, const mymap* t = nullptr) : node(n), tree(t) {}

        // dereference returns reference to node's pair
        value_type& operator*() const { return node->kv; }
        value_type* operator->() const { return &(node->kv); }

        iterator& operator++() {
            if (!node) return *this;
            if (node->right) {
                node = tree->minValueNode(node->right);
            } else {
                node_type* p = node->parent;
                while (p && node == p->right) {
                    node = p;
                    p = p->parent;
                }
                node = p;
            }
            return *this;
        }
        iterator operator++(int) { iterator tmp = *this; ++(*this); return tmp; }

        iterator& operator--() {
            // --end() => last element
            if (!node) {
                node = tree->maxValueNode(tree->root);
                return *this;
            }
            if (node->left) {
                node = tree->maxValueNode(node->left);
            } else {
                node_type* p = node->parent;
                while (p && node == p->left) {
                    node = p;
                    p = p->parent;
                }
                node = p;
            }
            return *this;
        }
        iterator operator--(int) { iterator tmp = *this; --(*this); return tmp; }

        bool operator==(const iterator& o) const { return node == o.node; }
        bool operator!=(const iterator& o) const { return node != o.node; }

    private:
        node_type* node;
        const mymap* tree;
    };

    iterator begin() { return iterator(minValueNode(root), this); }
    iterator end()   { return iterator(nullptr, this); }

    

    void clear() {
        clear(root);
        root = nullptr;
        _size = 0;
    }

private:
    node_type* root;
    std::size_t _size;

    // helpers
    void clear(node_type* n) {
        if (!n) return;
        clear(n->left);
        clear(n->right);
        delete n;
    }

    node_type* minValueNode(node_type* n) const {
        if (!n) return nullptr;
        while (n->left) n = n->left;
        return n;
    }
    node_type* maxValueNode(node_type* n) const {
        if (!n) return nullptr;
        while (n->right) n = n->right;
        return n;
    }

    node_type* successor(node_type* n) const {
        if (!n) return nullptr;
        if (n->right) return minValueNode(n->right);
        node_type* p = n->parent;
        while (p && n == p->right) { n = p; p = p->parent; }
        return p;
    }
    node_type* predecessor(node_type* n) const {
        if (!n) return nullptr;
        if (n->left) return maxValueNode(n->left);
        node_type* p = n->parent;
        while (p && n == p->left) { n = p; p = p->parent; }
        return p;
    }

    void rotateLeft(node_type* x) {
        if (!x) return;
        node_type* y = x->right;
        if (!y) return;
        x->right = y->left;
        if (y->left) y->left->parent = x;
        y->parent = x->parent;
        if (!x->parent) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void rotateRight(node_type* x) {
        if (!x) return;
        node_type* y = x->left;
        if (!y) return;
        x->left = y->right;
        if (y->right) y->right->parent = x;
        y->parent = x->parent;
        if (!x->parent) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        y->right = x;
        x->parent = y;
    }

    void fixInsert(node_type* z) {
        while (z->parent && z->parent->color == RED) {
            node_type* parent = z->parent;
            node_type* grand = parent->parent;
            if (!grand) break;
            if (parent == grand->left) {
                node_type* uncle = grand->right;
                if (uncle && uncle->color == RED) {
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    grand->color = RED;
                    z = grand;
                } else {
                    if (z == parent->right) {
                        z = parent;
                        rotateLeft(z);
                        parent = z->parent;
                        grand = parent ? parent->parent : nullptr;
                    }
                    parent->color = BLACK;
                    if (grand) grand->color = RED;
                    if (grand) rotateRight(grand);
                }
            } else {
                node_type* uncle = grand->left;
                if (uncle && uncle->color == RED) {
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    grand->color = RED;
                    z = grand;
                } else {
                    if (z == parent->left) {
                        z = parent;
                        rotateRight(z);
                        parent = z->parent;
                        grand = parent ? parent->parent : nullptr;
                    }
                    parent->color = BLACK;
                    if (grand) grand->color = RED;
                    if (grand) rotateLeft(grand);
                }
            }
        }
        if (root) root->color = BLACK;
    }
};

// public methods implementations (outside class for clarity)
template <typename Key, typename Value>
void mymap<Key, Value>::insert(const Key& key, const Value& value) {
    node_type* z = new node_type(key, value);
    if (!root) {
        z->color = BLACK;
        root = z;
        ++_size;
        return;
    }
    node_type* cur = root;
    node_type* parent = nullptr;
    while (cur) {
        parent = cur;
        if (key < cur->kv.first) cur = cur->left;
        else if (key > cur->kv.first) cur = cur->right;
        else { // update existing
            cur->kv.second = value;
            delete z;
            return;
        }
    }
    z->parent = parent;
    if (key < parent->kv.first) parent->left = z;
    else parent->right = z;
    ++_size;
    fixInsert(z);
}

template <typename Key, typename Value>
Value* mymap<Key, Value>::find(const Key& key) const{
    node_type* cur = root;
    while (cur) {
        if (key == cur->kv.first) return &(cur->kv.second);
        cur = (key < cur->kv.first) ? cur->left : cur->right;
    }
    return nullptr;
}

template <typename Key, typename Value>
Value& mymap<Key, Value>::operator[](const Key& key) {
    Value* p = find(key);
    if (p) return *p;
    insert(key, Value());
    p = find(key);
    return *p;
}

template <typename Key, typename Value>
Value& mymap<Key, Value>::at(const Key& key) const {
    Value* p = find(key);
    if (!p) throw std::out_of_range("Key not found in mymap");
    return *p;
}

#endif 
