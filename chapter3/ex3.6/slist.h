#ifndef SLIST_H
#define SLIST_H

#include "algorithm.h"

template <typename T>
class slist {
    struct node {
        union { T data, element; };
        node* next;
        node(const T& x=T(), node* N=0) : data(x),next(N) {}
    };

public:
    class iterator {
        node* ptr;
    public:
        iterator(node* P=0) : ptr(P) {}
        
        iterator& operator++()    { ptr = ptr->next; return *this; }
        iterator  operator++(int) { iterator it(ptr); ptr = ptr->next; return it; }
        T&        operator* ()                     { return ptr->next->data; }
		//bool operator==(const iterator& rhs) const { return ptr == rhs.ptr; }
        bool operator==(const iterator& rhs) const { return ptr->next==rhs.ptr->next; }
        bool operator!=(const iterator& rhs) const { return ptr->next!=rhs.ptr->next; }

        friend class slist;
    };

    class const_iterator {
        node* ptr;
    public:
        const_iterator(node* P=0) : ptr(P) {}
        
        const_iterator& operator++()        { ptr = ptr->next; return *this; }
        const_iterator  operator++(int)     { const_iterator it(ptr); ptr = ptr->next; return it; }
        const T&        operator*()         const { return ptr->next->data; }
        bool operator==(const_iterator rhs) const { return ptr->next==rhs.ptr->next; }
        bool operator!=(const_iterator rhs) const { return ptr->next!=rhs.ptr->next; }

        friend class slist;
    };

    slist() : head(new node) { rear = head; }
    slist(const slist& rhs) : head(new node) {
        rear = head;
        node *p = head, *q = rhs.head;
        while (q != rhs.rear) { insert(p, new node(*(q=q->next))); p = p->next; }
    }
   ~slist() { clear(); delete head; }

    slist& operator=(const slist& rhs) {
       if (&rhs != this) {
           clear();
           node *p = head, *q = rhs.head;
           while (q != rhs.rear) { insert(p, new node(*(q=q->next))); p = p->next; }
       }
       return *this;
    }

    iterator begin() { return iterator(head); }
    iterator   end() { return iterator(rear); }

    const_iterator cbegin() const { return const_iterator(head); }
    const_iterator   cend() const { return const_iterator(rear); }

          iterator find(const T& x)       { return DSAA::find( begin(),  end(), x); }
    const_iterator find(const T& x) const { return DSAA::find(cbegin(), cend(), x); }

    template <typename Iterator>
    iterator insert_before(iterator pos, Iterator src) { return insert(pos.ptr, *src); }
    iterator insert_before(iterator pos, const T& x) { return insert(pos.ptr, new node(x)); }
    template <typename Iterator>
    iterator insert_before(iterator pos, Iterator first, Iterator second) {
        while (first != second) { insert(pos, *first++); ++pos; }
        return pos;
    }

    template <typename Iterator>
    iterator insert(iterator pos, Iterator src) { return insert(pos.ptr, *src); }
    iterator insert(iterator pos, const T& x) { return insert(pos.ptr, new node(x)); }
    template <typename Iterator>
    iterator insert(iterator pos, Iterator first, Iterator second) {
        while (first != second) { insert(pos, *first++); ++pos; }
        return pos;
    }

    bool empty() const { return head == rear; }
    void clear() { remove(begin(), end()); rear = head; }

    bool remove(iterator it) { return it != end() ? (erase(it.ptr), 1) : 0; }
    bool remove(const T& x) { return remove(find(x)); }
    void remove(iterator first, iterator second) { while (first != second) erase(first.ptr); }

    void push_front(const T& x) { insert(head, x); }
    void push_back (const T& x) { insert(rear, x); }

    void pop_front() { erase(head); }

          T& front()       { return head->next->data; }
    const T& front() const { return head->next->data; }

          T& back ()       { return rear->data; }
    const T& back () const { return rear->data; }

private:
    node *head, *rear;

    node* insert(node* p, node* q) { q->next = p->next; p->next = q; if (rear == p) rear = q; return q; }
    node* insert(node* p, const T& x) { return insert(p, new node(x)); }
    void  erase (node* p) { node* q = p->next; p->next = q->next; if (q == rear) rear = p; delete q; }
};


#endif
//*/