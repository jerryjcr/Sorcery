#ifndef OBJECT_H_
#define OBJECT_H_

class Subject;

class Observer {
  Subject* s;

  public:
    virtual ~Observer() = default;

    void notify(Subject* whoFrom);
};

#endif
