## select、poll 和 epoll 的区别

- **select** 方法监控多个文件描述符，当某些文件描述符就绪（即，可以非阻塞地读写或出现异常）时，它能够通知程序。select的主要限制是单次能够监控的文件描述符数量有上限（通常是1024）。
- **poll** 方法与select类似，但是它不受最大文件描述符数量的限制。poll使用一个pollfd的数组来存储监控的文件描述符。尽管poll解决了文件描述符数量的限制，但在处理大量文件描述符时，性能仍然不是很高，因为它需要遍历整个数组来检查就绪的文件描述符。
- **epoll** 是Linux特有的I/O事件通知机制，相对于select和poll来说，提供了更高的性能。epoll能够无限制地监视大量的文件描述符，而且在活动的文件描述符较少时，效率更高。epoll使用一种事件驱动的方式，只关注活跃的文件描述符，而不是像select和poll那样轮询所有文件描述符。

## epoll 的文件描述符是无限的吗？

### 影响文件描述符最大数量的因素

1. **操作系统限制**：不同的操作系统和操作系统版本可能有不同的文件描述符限制。这些限制可以分为系统级别和用户级别。
2. **系统级别限制**：系统级别的限制定义了整个系统中所有进程能够打开的文件描述符的最大数量。在Linux系统中，这个限制可以通过`/proc/sys/fs/file-max`文件查看和设置。
3. **用户级别限制**：用户级别的限制定义了单个用户可以打开的文件描述符的最大数量。这个限制通常可以通过`ulimit`命令（shell内置命令）或修改用户的限制配置文件（如`/etc/security/limits.conf`）来查看和设置。

### 文件描述符数量的数据类型

文件描述符通常是一个非负整数。在编程接口（如POSIX或Linux API）中，文件描述符通常表示为`int`类型。文件描述符的值从3开始（在标准UNIX系统中，0、1和2分别被标准输入、标准输出和标准错误使用），并且随着新的文件或其他资源被打开而递增。

### 修改文件描述符限制

- **临时修改**：可以使用`ulimit -n [数量]`命令临时提高当前shell会话的文件描述符限制。
- **永久修改**：编辑`/etc/security/limits.conf`文件，添加或修改类似下面的行来设置软限制（soft limit）和硬限制（hard limit）：

## epoll 需要将描述符拷贝到用户态吗？

epoll在工作时，不需要将所有监控的文件描述符拷贝到用户态。它仅仅在`epoll_wait`调用时，将就绪的事件拷贝到用户空间。这是epoll相比于select和poll效率更高的一个原因。

## epoll 的流程

简化版的epoll使用流程如下：

1. **创建epoll对象**：通过`epoll_create`函数创建一个epoll对象。
2. **添加/修改/删除文件描述符**：使用`epoll_ctl`函数来添加、修改或删除要监视的文件描述符及其关注的事件。
3. **等待事件**：调用`epoll_wait`函数等待感兴趣的事件发生。`epoll_wait`会阻塞直到有事件发生，然后返回就绪的事件。

## epoll常用函数

### 1. `epoll_create`

`epoll_create`函数用于创建一个epoll的实例，它返回一个epoll的文件描述符，后续的操作都需要使用这个描述符。

```c
#include <sys/epoll.h>

int epoll_create(int size);
```

- **参数**：
  - `size`：这个参数在较新的Linux内核中已经被忽略，但为了向后兼容，需要传入一个大于0的值。
- **返回值**：成功时，返回一个非负的文件描述符。失败时，返回-1，并设置errno。

### 示例：

```c
int epoll_fd = epoll_create(1); // size参数只需大于0
if (epoll_fd == -1) {
    perror("epoll_create failed");
    exit(EXIT_FAILURE);
}
```

### 2. `epoll_ctl`

`epoll_ctl`函数用于控制某个epoll文件描述符上的事件，可以添加、修改或删除监视的文件描述符。

```c
#include <sys/epoll.h>

int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
```

- **参数**：
  - `epfd`：epoll实例的文件描述符。
  - `op`：要进行的操作，比如`EPOLL_CTL_ADD`、`EPOLL_CTL_MOD`、`EPOLL_CTL_DEL`。
  - `fd`：关联的目标文件描述符。
  - `event`：指向`epoll_event`结构的指针，指定事件类型和用户数据。
- **返回值**：成功时，返回0。失败时，返回-1，并设置errno。

### 示例：

```c
struct epoll_event ev;
ev.events = EPOLLIN; // 监视读取操作
ev.data.fd = sockfd; // sockfd是你要监视的socket文件描述符
if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, sockfd, &ev) == -1) {
    perror("epoll_ctl: add");
    exit(EXIT_FAILURE);
}
```

### 3. `epoll_wait`

`epoll_wait`函数等待epoll实例上的事件发生，它可以返回多个事件，由调用者处理。

```c
#include <sys/epoll.h>

int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);
```

- **参数**：
  - `epfd`：epoll实例的文件描述符。
  - `events`：用于从内核得到事件的集合。
  - `maxevents`：告诉内核这个events有多大，这个值不能大于创建epoll_create()时的size。
  - `timeout`：等待I/O事件发生的超时值（毫秒），-1表示无限等待。
- **返回值**：成功时，返回就绪的文件描述符数量。失败时，返回-1，并设置errno。

### 示例：

```c
const int MAX_EVENTS = 10;
struct epoll_event events[MAX_EVENTS];

int nfds = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
if (nfds == -1) {
    perror("epoll_wait");
    exit(EXIT_FAILURE);
}

for (int n = 0; n < nfds; ++n) {
    if (events[n].data.fd == sockfd) {
        // 处理sockfd上的事件
    }
}
```

通过这些示例，你可以看到如何创建epoll实例，如何向epoll实例添加监视的文件描述符以及如何等待事件发生并进行处理。这就是epoll的基本使用流程。

## `epoll_wait` 返回时的事件传递方式

`epoll_wait`返回时，并不是使用共享内存的方式直接让用户态和内核态共享就绪链表。而是内核将就绪的事件拷贝到用户态提供的缓冲区中。这意味着用户程序和内核空间在处理就绪事件时是分离的，用户程序通过`epoll_wait`调用获得的是就绪事件的一个副本。