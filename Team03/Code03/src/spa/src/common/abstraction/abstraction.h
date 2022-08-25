//
// Created by Josiah Khoo on 24/8/22.
//

#ifndef SPA_ABSTRACTION_H
#define SPA_ABSTRACTION_H

// Abstraction template that specifies two things, a left hand side class and a
// right hand side class.
template <class T, class U> class Abstraction {
public:
  // Gets the left hand side of the abstraction.
  virtual const T &GetLeftHandSide() const = 0;

  // Gets the right hand side of the abstraction.
  virtual const U &GetRightHandSide() const = 0;
};

#endif // SPA_ABSTRACTION_H
