/*
 * @Author: Clark
 * @Email: haixuanwoTxh@gmail.com
 * @Date: 2024-12-11 18:43:32
 * @LastEditors: Clark
 * @LastEditTime: 2024-12-11 18:54:33
 * @Description: file content
 */

#include <iostream>
#include <unistd.h>
#include <sys/epoll.h>
#include <sys/eventfd.h>
#include <pthread.h>

void* thread_func(void* arg)
{
    int efd = *reinterpret_cast<int*>(arg);
    uint64_t u = 1;

    for (int i = 0; i < 5; ++i)
    {
        sleep(1);
        u = i+1;
        write(efd, &u, sizeof(uint64_t));
        std::cout << "子线程：发送第 " << (i + 1) << " 个事件" << std::endl;
    }

    return nullptr;
}

int main()
{
    int efd = eventfd(0, EFD_NONBLOCK);
    if (efd == -1) {
        perror("eventfd");
        exit(EXIT_FAILURE);
    }

    int epfd = epoll_create1(0);
    if (epfd == -1) {
        perror("epoll_create1");
        close(efd);
        exit(EXIT_FAILURE);
    }

    struct epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = efd;
    if (epoll_ctl(epfd, EPOLL_CTL_ADD, efd, &event) == -1) {
        perror("epoll_ctl");
        close(epfd);
        close(efd);
        exit(EXIT_FAILURE);
    }

    pthread_t thread;
    pthread_create(&thread, nullptr, thread_func, &efd);

    for (int i = 0; i < 5; ++i)
    {
        struct epoll_event events[1];
        int n = epoll_wait(epfd, events, 1, -1);
        if (n == -1) {
            perror("epoll_wait");
            break;
        }

        if (events[0].data.fd == efd) {
            uint64_t u;
            read(efd, &u, sizeof(uint64_t));
            std::cout << "主线程：接收到第 " << (i + 1) << " 个事件，计数：" << u << std::endl;
        }
    }

    pthread_join(thread, nullptr);
    close(epfd);
    close(efd);
    return 0;
}
