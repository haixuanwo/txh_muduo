#include "thread/Atomic.h"
#include "datetime/Timestamp.h"
#include "Acceptor.h"
#include "InetAddress.h"
#include "TcpStream.h"

#include <string.h>
#include <thread>
#include <iostream>

muduo::AtomicInt64 g_bytes;

std::string getMessage()
{
  std::string line;
  for (int i = 33; i < 127; ++i)
  {
    line.push_back(char(i));
  }
  line += line;

  std::string message;
  for (size_t i = 0; i < 127-33; ++i)
  {
    message += line.substr(i, 72) + '\n';
  }
  return message;
}

void measure()
{
  muduo::Timestamp start = muduo::Timestamp::now();
  while (true)
  {
    struct timespec ts = { 1, 0 };
    ::nanosleep(&ts, NULL);
    // unfortunately, those two assignments are not atomic
    int64_t bytes = g_bytes.getAndSet(0);
    muduo::Timestamp end = muduo::Timestamp::now();
    double elapsed = timeDifference(end, start);
    start = end;
    if (bytes)
    {
      printf("%.3f MiB/s\n", bytes / (1024.0 * 1024) / elapsed);
    }
  }
}

void chargen(TcpStreamPtr stream)
{
  std::string message = getMessage();
  while (true)
  {
    int nw = stream->sendAll(message.data(), message.size());
    g_bytes.add(nw);
    if (nw < static_cast<int>(message.size()))
    {
      break;
    }
  }
  std::cout << "chargen end" << std::endl;
}

// a thread-per-connection current chargen server and client
int main(int argc, char* argv[])
{
  if (argc < 3)
  {
    printf("Usage:\n  %s hostname port\n  %s -l port\n", argv[0], argv[0]);
    std::string message = getMessage();
    printf("message size = %zd\n", message.size());
    return 0;
  }

  std::thread(measure).detach();

  int port = atoi(argv[2]);
  if (strcmp(argv[1], "-l") == 0)
  {
    InetAddress listenAddr(port);
    Acceptor acceptor(listenAddr);
    printf("Accepting... Ctrl-C to exit\n");
    int count = 0;
    while (true)
    {
      TcpStreamPtr tcpStream = acceptor.accept();
      printf("accepted no. %d client\n", ++count);

      std::thread thr(chargen, std::move(tcpStream));
      thr.detach();
    }
  }
  else
  {
    InetAddress addr;
    const char* hostname = argv[1];
    if (InetAddress::resolve(hostname, port, &addr))
    {
      TcpStreamPtr stream(TcpStream::connect(addr));
      if (stream)
      {
        chargen(std::move(stream));
      }
      else
      {
        printf("Unable to connect %s\n", addr.toIpPort().c_str());
        perror("");
      }
    }
    else
    {
      printf("Unable to resolve %s\n", hostname);
    }
  }
}
