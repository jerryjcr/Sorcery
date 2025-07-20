#ifndef OBJECT_H
#define OBJECT_H

class Subject;

class Observer {
  Subject* s;

  public:
    virtual ~Observer() = default;

    void notify(Subject* whoFrom);
};

#endif
