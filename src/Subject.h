#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>

class Observer;

class Subject {
  std::vector<Observer*> observers;

 public:
  virtual ~Subject() = default;

  void attach(Observer* o);
  void detach(Observer* o);
  void notifyObservers();
};

#endif
