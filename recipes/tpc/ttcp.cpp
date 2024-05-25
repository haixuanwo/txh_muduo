/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-05-25 15:19:43
 * @LastEditors: Clark
 * @LastEditTime: 2024-05-25 17:00:22
 * @Description: file content
 */
#include <iostream>
#include <string>
#include <sys/time.h>
#include <boost/program_options.hpp>

#include "Common.h"
#include "Acceptor.h"
#include "InetAddress.h"
#include "TcpStream.h"

struct Options {
    uint16_t port;
    int length;
    int number;
    bool transmit, receive, nodelay;
    std::string host;

    Options()
        : port(0), length(0), number(0), transmit(false), receive(false), nodelay(false), host("")
    {

    }
};

struct SessionMessage
{
    int32_t number;
    int32_t length;
} __attribute__((packed));

struct PayloadMessage
{
    int32_t length;
    char data[0];
};

// rewrite with getopt(3)
bool parseCommandLine(int argc, char* argv[], Options* opt)
{
    namespace po = boost::program_options;

    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "produce help message")
        ("port,p", po::value<uint16_t>(&opt->port)->default_value(5001), "TCP port")
        ("length,l", po::value<int>(&opt->length)->default_value(65536), "Buffer length")
        ("number,n", po::value<int>(&opt->number)->default_value(8192), "Number of buffers")
        ("trans,t", po::value<std::string>(&opt->host), "Transmit")
        ("recv,r", "Receive")
        ("nodelay,D", "set TCP_NODELAY")
        ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    opt->transmit = vm.count("trans");
    opt->receive = vm.count("recv");
    opt->nodelay = vm.count("nodelay");
    if (vm.count("help") || opt->port == 0)
    {
        std::cout << desc << std::endl;
        return false;
    }

    if (opt->transmit == opt->receive)
    {
        std::cerr << "either -t or -r must be specified." << std::endl;
        return false;
    }

    printf("port=%d\n", opt->port);
    if (opt->transmit)
    {
        printf("bufferr length = %d\n", opt->length);
        printf("number of bbuffers = %d\n", opt->number);
    }
    else
    {
        printf("Accepting...\n");
    }

    return true;
}

void transmit(const Options& opt)
{
    InetAddress addr(opt.host, opt.port);
    if (!InetAddress::resolve(opt.host, &addr))
    {
        std::cerr << "Unable to resolve %s " << opt.host << ":" << opt.port << std::endl;
        return;
    }

    printf("Connecting to %s:%d...\n", opt.host.c_str(), opt.port);
    TcpStreamPtr stream(TcpStream::connect(addr));
    if (!stream)
    {
        std::cerr << "Failed to connect to " << opt.host << ":" << opt.port << std::endl;
        return;
    }

    if (opt.nodelay)
    {
        stream->setTcpNoDelay(true);
    }
    printf("Connected.\n");

    double start = now_seconds();
    struct SessionMessage msg = {0, 0};
    msg.number = htonl(opt.number);
    msg.length = htonl(opt.length);

    if (stream->sendAll(&msg, sizeof(msg)) != sizeof(msg))
    {
        std::cerr << "Failed to send session message." << std::endl;
        perror("");
        return;
    }

    const int total_len = sizeof(int32_t) + opt.length;
    PayloadMessage* payload = static_cast<PayloadMessage*>(::malloc(total_len));
    std::unique_ptr<PayloadMessage, void(*)(void*)> freeIt(payload, ::free);
    assert(payload);
    payload->length = htonl(opt.length);

    for (int i = 0; i < opt.length; ++i)
    {
        payload->data[i] = "0123456789ABCDEF"[i % 16];
    }

    double total_mb = 1.0 * opt.number * opt.length / 1024 / 1024;
    printf("Sending %d buffers of length %d bytes (%.3f MB)...\n", opt.number, opt.length, total_mb);

    for (int i = 0; i < opt.number; ++i)
    {
        int nw = stream->sendAll(payload, total_len);
        assert(nw == total_len);

        int ack = 0;
        int nr = stream->receiveAll(&ack, sizeof(ack));
        assert(nr == sizeof(ack));
        ack = ntohl(ack);
        assert(ack == opt.length);
    }

    double elapsed = now_seconds() - start;
    printf("Sent %d buffers in %.3f seconds, %.3f MB/s\n", opt.number, elapsed, total_mb / elapsed);
}

void reiceve(const Options& opt)
{
    Acceptor acceptor(InetAddress(opt.port));
    TcpStreamPtr stream(acceptor.accept());

    if (!stream)
    {
        std::cerr << "Failed to accept connection." << std::endl;
        return;
    }

    struct SessionMessage msg = {0, 0};
    if (stream->receiveAll(&msg, sizeof(msg)) != sizeof(msg))
    {
        std::cerr << "Failed to receive session message." << std::endl;
        return;
    }

    msg.number = ntohl(msg.number);
    msg.length = ntohl(msg.length);
    printf("Received session message: number=%d, length=%d\n", msg.number, msg.length);

    double total_mb = 1.0 * msg.number * msg.length / 1024 / 1024;
    printf("Receiving %d buffers of length %d bytes (%.3f MB) total...\n", msg.number, msg.length, total_mb);

    const int total_len = sizeof(int32_t) + msg.length;
    PayloadMessage* payload = static_cast<PayloadMessage*>(::malloc(total_len));
    std::unique_ptr<PayloadMessage, void(*)(void*)> freeIt(payload, ::free);
    assert(payload);

    double start = now_seconds();
    for (int i = 0; i < msg.number; ++i)
    {
        payload->length = 0;
        if (stream->receiveAll(&payload->length, sizeof(payload->length)) != sizeof(payload->length))
        {
            std::cerr << "Failed to receive payload message." << std::endl;
            return;
        }

        payload->length = ntohl(payload->length);
        assert(payload->length == msg.length);
        if (stream->receiveAll(payload->data, payload->length) != payload->length)
        {
            perror("read payload data");
            return;
        }

        int32_t ack = htonl(payload->length);
        if (stream->sendAll(&ack, sizeof(ack)) != sizeof(ack))
        {
            std::cerr << "Failed to send ack." << std::endl;
            return;
        }
    }

    double elapsed = now_seconds() - start;
    printf("Received %d buffers in %.3f seconds, %.3f MB/s total\n", msg.number, elapsed, total_mb / elapsed);
}

int main(int argc, char* argv[])
{
    Options opt;
    if (parseCommandLine(argc, argv, &opt))
    {
        if (opt.transmit)
        {
            transmit(opt);
        }
        else if (opt.receive)
        {
            reiceve(opt);
        }
        else
        {
            assert(false);
        }
    }

    return 0;
}
