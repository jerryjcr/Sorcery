#ifndef OBSERVER_H_
#define OBSERVER_H_

class Subject;

class Observer {
  Subject* subject;

  public:
    virtual ~Observer() = default;

    void notify(Subject* whoFrom);
};

#endif
