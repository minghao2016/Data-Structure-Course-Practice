/* algorithm.h
******************************************************************************/
/* OS           : GNU/Linux 3.11.8-200.fc19.i686.PAE #1 SMP 2013-11-14
 * Compiler     : g++ (GCC) 4.8.2 20131017 (Red Hat 4.8.2-1)
 * Encoding     : UTF8
 * Date         : 2013-11-22
 *
 * Note:
 * If you can't read the Chinese characters in this file, you may try to setup
 * the encoding of your operating system or your reader to Unicode-8. You may
 * also convert the encoding of this file to your encoding by some encoding
 * converting software.
 *
 * All Rights Reserved by Prinse Wang, Goldwe Tech, Inc.
 *****************************************************************************/
/* Description: ***************************************************************
 *****************************************************************************/
/* Analysis: ******************************************************************
 *****************************************************************************/
//*
#ifndef ALGORITHM_H
#define ALGORITHM_H

namespace DSAA {

template <typename T>
struct assign {
    T x;
    assign(const T& X) : x(X) {}
          T& operator* () { return x; }
    const T& operator* () const { return x; }
          T& operator()(T& y) { return y=x; }
          T& operator()(T& y, const T& X) { return y=x=X; }
};

template <typename T, typename action=assign<T> >
struct sequence {
    action f;
    int pos;
    sequence(action F, int P=0) : f(F),pos(P) {}

    sequence&   operator++()                          { ++pos; return *this; }
    sequence&   operator--()                          { --pos; return *this; }
    sequence    operator++(int)                       { return sequence(f,pos++); }
    sequence    operator--(int)                       { return sequence(f,pos--); }
    sequence    operator+ (int n)               const { return sequence(f,pos+n); }
    sequence    operator- (int n)               const { return sequence(f,pos-n); }
    int         operator- (const sequence& rhs) const { return pos - rhs.pos; }

    bool        operator==(const sequence& rhs) const { return pos==rhs.pos; }
    bool        operator!=(const sequence& rhs) const { return pos!=rhs.pos; }
    bool        operator<=(const sequence& rhs) const { return pos<=rhs.pos; }
    bool        operator>=(const sequence& rhs) const { return pos>=rhs.pos; }
    bool        operator< (const sequence& rhs) const { return pos< rhs.pos; }
    bool        operator> (const sequence& rhs) const { return pos> rhs.pos; }

          T&    operator* ()                          { return *f; }
    const T&    operator* ()                    const { return *f; }

          T&    operator()()                          { return pos; }
    const T&    operator()()                    const { return pos; }
          T&    operator()(T& y)                      { return f(y); }
};

template <typename Iter, typename T>
Iter find(Iter it1, Iter it2, const T& x) { while (it1 != it2 && *it1 != x) ++it1; return it1; }

template <typename Iter1, typename Iter2>
Iter1 copy(Iter1 d, Iter2 it1, Iter2 it2) { while (it1 != it2) *d++ = *it1++; return d; }

template <typename Iter1, typename Iter2>
Iter1 rcopy(Iter1 d, Iter2 it1, Iter2 it2) { while (it1 != it2) *d++ = *it2--; return d; }

template <typename Iter, typename action>
void for_each(Iter it1, Iter it2, action act) { while (it1 != it2) act(*it1++); }

template <typename Iter1, typename Iter2, typename action>
void for_each(Iter1 d, Iter2 it1, Iter2 it2, action act) { while (it1 != it2) act(*d, *it1++); }

template <typename Iter1, typename Iter2, typename action>
void zip_each(Iter1 d, Iter2 it1, Iter2 it2, action act) { while (it1 != it2) act(*d, *it1++),++d; }

template <typename Iter, typename action>
void rfor_each(Iter it1, Iter it2, action act) { while (it1 != it2) act(*it2--); }

template <typename Iter1, typename Iter2, typename action>
void rfor_each(Iter1 d, Iter2 it1, Iter2 it2, action act) { while (it1 != it2) act(*d, *it2--); }

template <typename Iter1, typename Iter2, typename action>
void rzip_each(Iter1 d, Iter2 it1, Iter2 it2, action act) { while (it1 != it2) act(*d, *it2--),++d; }

};

#endif
