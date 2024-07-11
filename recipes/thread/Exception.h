/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-07-10 15:36:10
 * @LastEditors: Clark
 * @LastEditTime: 2024-07-10 15:36:15
 * @Description: file content
 */

#include <exception>
#include <string>

namespace muduo
{

class Exception : public std::exception
{
 public:
  explicit Exception(const char* what);
  virtual ~Exception() throw();
  virtual const char* what() const throw();
  const char* stackTrace() const throw();

 private:
  std::string message_;
  std::string stack_;
};

}
