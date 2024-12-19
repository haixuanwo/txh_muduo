/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-07-27 15:37:11
 * @LastEditors: Clark
 * @LastEditTime: 2024-07-27 15:42:33
 * @Description: file content
 */
#include "codec.h"

using namespace muduo;
using namespace muduo::net;
using namespace pubsub;

ParseResult pubsub::parseMessage(Buffer* buf,
                                 string* cmd,
                                 string* topic,
                                 string* content)
{
  ParseResult result = kError;
  const char* crlf = buf->findCRLF();
  if (crlf)
  {
    const char* space = std::find(buf->peek(), crlf, ' '); // 跳过空格
    if (space != crlf)
    {
      cmd->assign(buf->peek(), space);  // 解析到cmd字段
      topic->assign(space+1, crlf);     // 解析到主题字段

      if (*cmd == "pub")
      {
        const char* start = crlf + 2;
        crlf = buf->findCRLF(start);
        if (crlf)
        {
          content->assign(start, crlf); // 解析到要发布的数据内容
          buf->retrieveUntil(crlf+2);
          result = kSuccess;
        }
        else
        {
          result = kContinue;
        }
      }
      else
      {
        buf->retrieveUntil(crlf+2);      // 丢弃换行符与之后的两个字节
        result = kSuccess;
      }
    }
    else
    {
      result = kError; // 无内容数据
    }
  }
  else
  {
    result = kContinue; // 数据未收完整，未收到数据结束换行符\n
  }
  return result;
}
