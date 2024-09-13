/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-09-13 13:52:52
 * @LastEditors: Clark
 * @LastEditTime: 2024-09-13 14:02:16
 * @Description: file content
 */
#include <algorithm>
#include <vector>
#include <stdio.h>
#include <memory>
// #include <thread>
#include <mutex>

class Observable;

class Observer : public std::enable_shared_from_this<Observer>
{
 public:
  virtual ~Observer();
  virtual void update() = 0;

  void observe(Observable* s);

 protected:
  Observable* subject_;
};

class Observable
{
 public:
  void register_(std::weak_ptr<Observer> x);
  // void unregister(std::weak_ptr<Observer> x);

  void notifyObservers()
  {
    std::lock_guard<std::mutex> lock(mutex_);
    Iterator it = observers_.begin();
    while (it != observers_.end())
    {
      std::shared_ptr<Observer> obj(it->lock());
      if (obj)
      {
        obj->update();
        ++it;
      }
      else
      {
        printf("notifyObservers() erase\n");
        it = observers_.erase(it);
      }
    }
  }

 private:
  mutable std::mutex mutex_;
  std::vector<std::weak_ptr<Observer> > observers_;
  typedef std::vector<std::weak_ptr<Observer> >::iterator Iterator;
};

Observer::~Observer()
{
  // subject_->unregister(this);
}

void Observer::observe(Observable* s)
{
  s->register_(shared_from_this());
  subject_ = s;
}

void Observable::register_(std::weak_ptr<Observer> x)
{
  observers_.push_back(x);
}

//void Observable::unregister(std::weak_ptr<Observer> x)
//{
//  Iterator it = std::find(observers_.begin(), observers_.end(), x);
//  observers_.erase(it);
//}

// ---------------------

class Foo : public Observer
{
  virtual void update()
  {
    printf("Foo::update() %p\n", this);
  }
};

int main()
{
  Observable subject;
  {
    std::shared_ptr<Foo> p(new Foo);
    p->observe(&subject);
    subject.notifyObservers();
  }
  subject.notifyObservers();
}

