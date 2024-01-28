## 参考

___

[Linux Socket编程（不限Linux） - 吴秦 - 博客园 (cnblogs.com)](https://www.cnblogs.com/skynet/archive/2010/12/12/1903949.html)

## 网络中进程之间如何通信

___

### 本地进程间通信（IPC）的分类

- 消息传递
  - 管道
  - FIFO
  - 消息队列
- 同步
  - 互斥量
  - 条件变量
  - 读写锁
  - 文件和写记录锁
  - 信号量
- 共享内存
  - 匿名的
  - 具名的
- 远程过程调用
  - Solaris门
  - Sun RPC

### 网络中进程间通信的问题和解决方法
- 问题：如何唯一标识网络中的进程
  - 在本地：通过进程PID
  - 在网络中：进程PID不适用
- 解决方法：利用TCP/IP协议族
  - 网络层：使用“ip地址”标识主机
  - 传输层：使用“协议+端口”标识主机中的应用程序（进程）
  - 三元组（ip地址，协议，端口）标识网络中的进程

### 网络进程通信的实现方式
- 使用TCP/IP协议的应用程序通常采用的应用编程接口：
  - UNIX BSD的套接字（socket）
  - UNIX System V的TLI（已被淘汰）
- 目前主流：几乎所有的应用程序都采用socket
- 重要性：网络时代下，网络中进程通信是无处不在的现象，体现了“一切皆socket”的观点。

## 什么是Socket？

___

### Socket的概念
- 基本定义：Socket起源于Unix，是一种特殊的文件。
- 基本哲学：Unix/Linux的哲学之一是“一切皆文件”，所有操作均可通过“打开open –> 读写write/read –> 关闭close”模式进行。
- Socket作为实现：在这种模式下，Socket就是一种特殊的文件实现。它主要用于网络中的进程通信。
- 操作方式：通过特定的Socket函数进行操作，如读/写IO、打开、关闭等。

### Socket一词的起源
- 首次使用：在组网领域，Socket一词首次出现于1970年2月12日发布的IETF RFC33文献中。
- 文献作者：Stephen Carr、Steve Crocker和Vint Cerf。
- 命名空间的元素：Croker在文献中描述，“命名空间的元素都可称为套接字接口。”
- 连接的定义：一个套接字接口构成一个连接的一端，一对套接字接口可完全规定一个连接。
- 计算机历史博物馆的补充：据美国计算机历史博物馆记载，这个定义比BSD的套接字接口定义早大约12年。

## Socket的基本操作

___

### 1. socket()函数
- 功能：创建一个socket描述符（socket descriptor），类似于文件操作中的打开（open）。
- 函数声明：`int socket(int domain, int type, int protocol);`
- 参数：
  - `domain`：协议域/族（protocol family），如AF_INET（IPv4网络协议）、AF_INET6（IPv6网络协议）、AF_LOCAL（Unix域socket）。
  - `type`：socket类型，如SOCK_STREAM（流式socket, TCP）、SOCK_DGRAM（数据报socket, UDP）。
  - `protocol`：指定协议，如IPPROTO_TCP（TCP传输协议）、IPPROTO_UDP（UDP传输协议）。当设置为0时，会自动选择对应的默认协议。
- 注意：不是所有的`type`和`protocol`组合都有效。例如，SOCK_STREAM不可以与IPPROTO_UDP组合。
- 返回值：创建的socket描述字，用于后续操作。

### 2. bind()函数
- 功能：将地址（IP + 端口号）绑定到socket描述符。
- 函数声明：`int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);`
- 参数：
  - `sockfd`：通过socket()函数创建的socket描述字。
  - `addr`：指向要绑定给socket的协议地址的指针。具体结构取决于地址协议族：
    - IPv4（AF_INET）：使用`struct sockaddr_in`。
    - IPv6（AF_INET6）：使用`struct sockaddr_in6`。
    - Unix域（AF_UNIX）：使用`struct sockaddr_un`。
  - `addrlen`：地址的长度。
- 作用：服务器通常在启动时使用bind()绑定一个众所周知的地址以提供服务，而客户端通常不需要调用bind()，系统会自动分配地址。

#### 网络字节序与主机字节序
- 主机字节序（大端和小端模式）：整数在内存中的保存顺序。
  - Little-Endian：低位字节在低地址端。
  - Big-Endian：高位字节在低地址端。
- 网络字节序：TCP/IP协议中整数的传输顺序，总是大端（Big-Endian）。
- 重要性：在绑定地址到socket时，需将主机字节序转换为网络字节序。错误处理字节序可能导致问题。

### 3 .listen()函数
- 用途：用于服务器监听特定的socket。
- 函数声明：
  - `int listen(int sockfd, int backlog);`
  - 这是该函数的标准C语言声明。它返回一个整数，表示函数调用是否成功。返回值为0表示成功，-1表示失败。
- 参数：
  - **`sockfd`（Socket描述字）**
    - 这个参数是一个整数，代表要监听的Socket的文件描述符。在调用`listen()`之前，此Socket应已被创建（通常是通过`socket()`函数）并且已经绑定到一个本地地址（通常是通过`bind()`函数）。
    - 例子：如果一个服务器程序在端口8080上监听，则首先通过`socket()`创建一个Socket，然后通过`bind()`将该Socket绑定到端口8080。之后，这个绑定到端口8080的Socket的文件描述符会作为`sockfd`参数传递给`listen()`。
  - **`backlog`（最大连接队列长度）**
    - 这个参数指定了服务器端Socket可以排队等待接受的最大客户端连接数。这并不是指最大连接数，而是在Socket开始拒绝新的连接请求之前，可以排队的未完成连接请求的数量。
    - 例子：如果`backlog`设置为5，那么在任何时候，都可以有5个客户端的连接处于等待状态。如果有更多的客户端尝试连接，而队列已满，则这些新的连接请求可能会被拒绝。
- 功能：
  - `listen()`的主要功能是将一个主动类型的Socket（即用于发起连接的Socket）转变为被动类型的Socket，专门用于监听和接受进入的连接请求。
  - 当`listen()`函数被调用后，相应的Socket进入监听模式，服务器就可以使用`accept()`函数来接受来自客户端的连接请求了。

### 4 .connect()函数
- 用途：客户端通过connect函数建立与TCP服务器的连接。
- 函数声明：
  - `int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);`
  - 此函数返回一个整数，成功时返回0，失败时返回-1。
- 参数：
  - **`sockfd`（客户端的Socket描述字）**
    - 这是一个由`socket()`函数返回的Socket描述符，用于标识客户端的Socket。
  - **`addr`（指向服务器的Socket地址）**
    - 这是一个指向`struct sockaddr`的指针，包含了目标服务器的地址信息（如IP地址和端口号）。
  - **`addrlen`（地址的长度）**
    - 表示`addr`指向的地址结构的大小。

### 5 .accept()函数
- 用途：服务器使用`accept()`函数来接受客户端的连接请求。
- 函数声明：
  - `int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);`
  - 此函数返回一个新的Socket描述字，用于与客户端的通信。
- 参数：
  - **`sockfd`（服务器的监听Socket描述字）**
    - 这是通过之前调用`socket()`和`listen()`得到的监听Socket的描述字。
  - **`addr`（用于返回客户端的协议地址）**
    - 这是一个指向`struct sockaddr`的指针，用于存储接受到的客户端地址信息。
  - **`addrlen`（地址的长度）**
    - 这是一个指向`socklen_t`类型变量的指针，初始时表示地址结构的大小，调用后表示实际存储在`addr`中的地址长度。
- 返回值：新的描述字，代表与客户端的TCP连接。

### 6. read()、write()等I/O函数
- 功能：进行网络I/O操作，类似于文件的读写操作。
- 常用函数：
  - **`read()`/`write()`**
    - 用于在已连接的套接字（socket）上进行数据的读取和写入。
    - `read(int fd, void *buf, size_t count);`
      1. `fd`: 文件描述符，这里特指socket的描述符。它是一个整数值，用于标识一个特定的socket。
      2. `buf`: 数据缓冲区的指针，这是一个指向内存位置的指针，在这个位置上，`read()`函数将存储读取的数据。
      3. `count`: 要读取的最大字节数。函数在读取了`count`字节数据或遇到文件结束时停止。
    - `write(int fd, const void *buf, size_t count);`
      1. `fd`: 同样是文件描述符，指的是要写入数据的socket。
      2. `buf`: 包含要写入数据的缓冲区的指针。这指向函数将发送或写入网络的数据。
      3. `count`: 要写入的字节数。
    - 这些函数直接操作socket描述字，不涉及特定的网络参数。
  - **`recv()`/`send()`**
    - 特别用于socket编程。
    - **`recv(int sockfd, void \*buf, size_t len, int flags);`**
      - `int sockfd`: 这是一个文件描述符，指向你想要接收数据的 socket。通常这个 socket 是由 `socket()` 函数创建，并通过 `connect()`（客户端）或 `accept()`（服务器端）与对方建立连接的。
      - `void *buf`: 这是一个指向缓冲区的指针，用于存储接收到的数据。开发者需要分配足够的空间以确保能够容纳预期接收的数据量。
      - `size_t len`: 这个参数指定了缓冲区的最大长度，即 `buf` 可以接收的最大数据量。
      - `int flags`: 这个参数用于指定接收操作的行为。例如，`MSG_PEEK` 标志允许查看接收缓冲区中的数据，而不会从缓冲区中移除它们，而 `MSG_WAITALL` 标志请求阻塞操作直到接收到请求的数据量。
    - **`send(int sockfd, const void \*buf, size_t len, int flags);`**
      - `int sockfd`: 同 `recv`，这是一个指向你想要发送数据的 socket 的文件描述符。
      - `const void *buf`: 这是一个指向你要发送的数据的指针。数据应该存储在这个缓冲区中。
      - `size_t len`: 这个参数指定了要发送的数据的大小。
      - `int flags`: 这个参数提供了额外的控制发送操作的方式。例如，`MSG_DONTROUTE` 标志用于告诉网络层不要进行路由，`MSG_NOSIGNAL` 在某些系统上用于防止在连接断开时发送 `SIGPIPE` 信号。
    - 提供了额外的控制，如指定特殊的行为标志。
  - **`recvfrom()`/`sendto()`**
    - 主要用于无连接的UDP协议。
    - 允许接收和发送数据时指定对方的地址。
  - **`recvmsg()`/`sendmsg()`**
    - 最通用和强大的I/O函数，允许更复杂的操作。
    - 提供了对多个缓冲区和辅助数据的操作。
- 这些函数在成功时返回实际读取或写入的字节数，失败时返回-1并设置errno变量以指示错误。

### 7.  close()函数
- 用途：关闭socket描述字。
- 函数声明：`int close(int fd);`
- 标记socket为已关闭，并立即返回。一旦调用`close()`，该描述字就不能再被用于任何读写操作。
- 关闭操作会减少socket描述字的引用计数。当引用计数降至0时，操作系统才会真正关闭socket，并释放相关资源。

#### 网络字节序与主机字节序的处理
- 在网络编程中，正确处理字节序（字节的顺序）是非常重要的。在进行socket编程时，通常需要将主机字节序转换为网络字节序，以确保数据在不同主机间正确传输。

## 步骤总结

___

### 服务端步骤

1. **创建Socket**
   - 使用`socket()`函数创建一个新的Socket。
   - 例：`int server_fd = socket(AF_INET, SOCK_STREAM, 0);`

2. **绑定Socket到地址**
   - 使用`bind()`函数将Socket绑定到服务器地址和端口。
   - 例：`bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));`

3. **监听连接**
   - 使用`listen()`函数使得Socket进入监听模式，准备接收客户端连接。
   - 例：`listen(server_fd, backlog);`

4. **接受连接**
   - 使用`accept()`函数接受来自客户端的连接请求。
   - 这会返回一个新的Socket描述字，用于与该客户端的通信。
   - 例：`int new_socket = accept(server_fd, (struct sockaddr *)&client_addr, (socklen_t*)&addrlen);`

5. **读写操作**
   - 使用`read()`或`write()`等函数进行数据的读取或发送。
   - 例：`read(new_socket, buffer, sizeof(buffer));`

6. **关闭Socket**
   - 使用`close()`函数关闭与客户端的连接。
   - 例：`close(new_socket);`

### 客户端步骤

1. **创建Socket**
   - 使用`socket()`函数创建一个新的Socket。
   - 例：`int sock = socket(AF_INET, SOCK_STREAM, 0);`

2. **建立连接**
   - 使用`connect()`函数连接到服务器的Socket。
   - 例：`connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));`

3. **读写操作**
   - 使用`send()`或`recv()`等函数进行数据的发送或接收。
   - 例：`send(sock, hello_message, strlen(hello_message), 0);`

4. **关闭Socket**
   - 使用`close()`函数关闭Socket连接。
   - 例：`close(sock);`

## 例子

___

### 服务器端代码

```c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define MAXLINE 4096

int main(int argc, char** argv)
{
    int    listenfd, connfd; // 监听和连接的文件描述符
    struct sockaddr_in     servaddr; // 服务端地址结构
    char    buff[4096]; // 缓冲区
    int     n;

    // 创建socket
    if( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1 ){
        printf("create socket error: %s(errno: %d)\n",strerror(errno),errno);
        exit(0);
    }

    // 初始化地址结构
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); // 任意IP地址
    servaddr.sin_port = htons(6666); // 端口号6666

    // 绑定socket与地址
    if( bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1){
        printf("bind socket error: %s(errno: %d)\n",strerror(errno),errno);
        exit(0);
    }

    // 监听端口
    if( listen(listenfd, 10) == -1){
        printf("listen socket error: %s(errno: %d)\n",strerror(errno),errno);
        exit(0);
    }

    printf("======waiting for client's request======\n");
    while(1){
        // 接受客户端连接
        if( (connfd = accept(listenfd, (struct sockaddr*)NULL, NULL)) == -1){
            printf("accept socket error: %s(errno: %d)",strerror(errno),errno);
            continue;
        }
        // 接收数据
        n = recv(connfd, buff, MAXLINE, 0);
        buff[n] = '\0';
        printf("recv msg from client: %s\n", buff);
        close(connfd); // 关闭连接
    }

    close(listenfd); // 关闭监听socket
}
```

### 客户端代码

```c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define MAXLINE 4096

int main(int argc, char** argv)
{
    int    sockfd, n; // socket文件描述符
    char    recvline[4096], sendline[4096]; // 接收和发送缓冲区
    struct sockaddr_in    servaddr; // 服务器地址结构

    // 检查参数
    if( argc != 2){
        printf("usage: ./client <ipaddress>\n");
        exit(0);
    }

    // 创建socket
    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("create socket error: %s(errno: %d)\n", strerror(errno),errno);
        exit(0);
    }

    // 初始化地址结构
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_port = htons(6666); // 端口号6666
    // 将IP地址从字符串转换为网络格式
    if( inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0){
        printf("inet_pton error for %s\n",argv[1]);
        exit(0);
    }

    // 连接服务器
    if( connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){
        printf("connect error: %s(errno: %d)\n",strerror(errno),errno);
        exit(0);
    }

    printf("send msg to server: \n");
    // 从stdin获取消息并发送
    fgets(sendline, 4096, stdin);
    if( send(sockfd, sendline, strlen(sendline), 0) < 0)
    {
        printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);
        exit(0);
    }

    close(sockfd); // 关闭socket
    exit(0);
}
```

注意：这些代码提供了一个基本的TCP服务器和客户端实现，但它们没有实现错误处理和安全性措施。在实际应用中，这些方面需要特别注意。另外，代码中服务器是以迭代方式运行的，意味着它一次只能处理一个客户端。对于更高效的处理，可以考虑使用多线程或多进程。

## 练习

___

服务器端：

接收地址192.168.100.2的客户端信息，如信息为“Client Query”，则打印“Receive Query”

客户端：

向地址192.168.100.168的服务器端顺序发送信息“Client Query test”，“Cleint Query”，“Client Query Quit”，然后退出。

题目中出现的ip地址可以根据实际情况定。

在Linux环境下使用C++实现服务器和客户端的程序，并添加中文注释，可以按照以下方式进行：

### 服务器端
1. 创建一个套接字（Socket）。
2. 绑定（Bind）套接字到指定的IP地址和端口。
3. 监听（Listen）连接。
4. 接受（Accept）客户端的连接。
5. 接收（Receive）来自客户端的消息。
6. 根据接收到的消息内容进行相应的处理。
7. 关闭套接字。

### 客户端
1. 创建一个套接字。
2. 连接（Connect）到服务器的IP地址和端口。
3. 发送（Send）消息到服务器。
4. 根据需要发送不同的消息。
5. 关闭套接字。

### 服务器端代码示例（server.cpp）
```cpp
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    
    // 创建套接字
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    
    // 绑定套接字到IP/端口
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);
    
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // 监听连接
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    // 接受连接
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    // 接收并回应消息
    while(true) {
        memset(buffer, 0, sizeof(buffer)); // 清空缓冲区
        int valread = read(new_socket, buffer, 1024);
        std::cout << "Received: " << buffer << std::endl;

        if (strcmp(buffer, "Client Query") == 0) {
            std::cout << "Receive Query" << std::endl;
        }
        else if (strcmp(buffer, "Client Query Quit") == 0) {
            break;
        }
    }

    // 关闭套接字
    close(server_fd);
    return 0;
}
```

### 客户端代码示例（client.cpp）
```cpp
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    const char* messages[3] = {"Client Query test", "Client Query", "Client Query Quit"};

    // 创建套接字
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);
    
    // 将IP地址从字符串转换为二进制形式
    if(inet_pton(AF_INET, "192.168.100.168", &serv_addr.sin_addr) <= 0) {
        perror("Invalid address/Address not supported");
        return -1;
    }

    // 连接到服务器
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection Failed");
        return -1;
    }

    // 发送消息
    for (int i = 0; i < 3; ++i) {
        send(sock, messages[i], strlen(messages[i]), 0);
        std::cout << "Message sent: " << messages[i] << std::endl;
    }

    // 关闭套接字
    close(sock);
    return 0;
}
```

