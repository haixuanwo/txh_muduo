#include "WeakCallback.h"

#include <iostream>
#include <stdio.h>
#include <boost/noncopyable.hpp>
#include <thread>

class String
{
 public:
  String(const char* str)
  {
    printf("String ctor this %p\n", this);
  }

  String(const String& rhs)
  {
    printf("String copy ctor this %p, rhs %p\n", this, &rhs);
  }

  String(String&& rhs)
  {
    printf("String move ctor this %p, rhs %p\n", this, &rhs);
  }
};

class Foo : boost::noncopyable
{
 public:
  void zero();
  void zeroc() const;
  void one(int);
  void oner(int&);
  void onec(int) const;
//   void oneString(const String& str);
  void oneString(String str);
  void oneStringRR(String&& str);
};

void Foo::zero()
{
  printf("Foo::zero()\n");
}

void Foo::zeroc() const
{
  printf("Foo::zeroc()\n");
}

void Foo::one(int x)
{
  printf("Foo::one() x=%d\n", x);
}

void Foo::oner(int& x)
{
  printf("Foo::oner() x=%d\n", x);
  x = 1000;
}

void Foo::onec(int x) const
{
  printf("Foo::onec() x=%d\n", x);
}

// void Foo::oneString(const String& str)
// {
//   printf("Foo::oneString\n");
// }

void Foo::oneString(String str)
{
  printf("Foo::oneString\n");
}

void Foo::oneStringRR(String&& str)
{
  printf("Foo::oneStringRR\n");
}

String getString()
{
  return String("zz");
}


int main1()
{
  String s("xx");
  Foo f;
  f.oneString(s);
//   f.oneString(String("yy"));
  // f.oneStringRR(s);
//   f.oneStringRR(String("yy"));
//   f.oneString(getString());
//   f.oneStringRR(getString());

  return 0;
}

int main2()
{
  printf("======== testWeakCallback \n");
  std::shared_ptr<Foo> foo(new Foo);
  muduo::WeakCallback<Foo> cb0 = muduo::makeWeakCallback(foo, &Foo::zero);
  muduo::WeakCallback<Foo> cb0c = muduo::makeWeakCallback(foo, &Foo::zeroc);
  cb0();
  cb0c();

  muduo::WeakCallback<Foo, int> cb1 = muduo::makeWeakCallback(foo, &Foo::one);
  auto cb1c = muduo::makeWeakCallback(foo, &Foo::onec);
  auto cb1r = muduo::makeWeakCallback(foo, &Foo::oner);
  cb1(123);
  cb1c(234);
  int i = 345;
  cb1r(i);
//   BOOST_CHECK_EQUAL(i, 1000);

  auto cb2 = muduo::makeWeakCallback(foo, &Foo::oneString);
  auto cb2r = muduo::makeWeakCallback(foo, &Foo::oneStringRR);
  printf("_Z%s\n", typeid(cb2).name());
  printf("_Z%s\n", typeid(cb2r).name());
  cb2(String("xx"));
  cb2r(String("yy"));

  muduo::WeakCallback<Foo> cb3(foo, std::bind(&Foo::oneString, std::placeholders::_1, "zz"));

  cb3();

  printf("======== reset \n");
  foo.reset();
  cb0();
  cb0c();
  cb1(123);
  cb1c(234);
  cb2(String("xx"));
  cb2r(String("yy"));
  cb3();

  return 0;
}

int main3()
{
    std::shared_ptr<Foo> foo(new Foo);
    muduo::WeakCallback<Foo> cb0 = muduo::makeWeakCallback(foo, &Foo::zero);
    muduo::WeakCallback<Foo> cb0c = muduo::makeWeakCallback(foo, &Foo::zeroc);
    cb0();
    cb0c();

    muduo::WeakCallback<Foo, int> cb1 = muduo::makeWeakCallback(foo, &Foo::one);
    auto cb1c = muduo::makeWeakCallback(foo, &Foo::onec);
    auto cb1r = muduo::makeWeakCallback(foo, &Foo::oner);
    cb1(123);
    cb1c(234);
    int i = 345;
    cb1r(i);

    foo.reset();
    cb0();
    cb0c();
    cb1(123);
    cb1c(234);
    cb1r(i);

    return 0;
}

int main()
{
    std::shared_ptr<Foo> foo(new Foo);

    std::thread t1([&](){
        muduo::WeakCallback<Foo> cb0 = muduo::makeWeakCallback(foo, &Foo::zero);
        while (1)
        {
            cb0();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            std::cout << "t1" << t1.get_id() << std::endl;
        }
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(3000));

    foo.reset();

    t1.join();

    return 0;
}
