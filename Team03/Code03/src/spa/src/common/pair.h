#ifndef SPA_PAIR_H
#define SPA_PAIR_H

// Template that specifies two things, a left hand side class and a
// right hand side class.
template<class T, class U>
class Pair {
public:
    // Gets the left hand side of the abstraction.
    virtual const T &GetLeftHandSide() const = 0;

    // Gets the right hand side of the abstraction.
    virtual const U &GetRightHandSide() const = 0;
};

#endif  // SPA_PAIR_H
