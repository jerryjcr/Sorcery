#ifndef SUBJECT_H_
#define SUBJECT_H_

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
