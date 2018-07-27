#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <udp_data_struct.h>

#define SERVER_PORT 8089
#define BUFF_LEN 1024

using namespace std;

udp_data udp_frame_send;
udp_data udp_frame_recv;
udp_data* udp_frame_send_ptr;
udp_data* udp_frame_recv_ptr;
char* udp_frame_send_ptr_char;
char* udp_frame_recv_ptr_char;

void handle_udp_msg(int fd) {
  char buf[BUFF_LEN];  //接收缓冲区，1024字节
  socklen_t sock_len;
  int count;
  struct sockaddr_in clent_addr;  // clent_addr用于记录发送方的地址信息
  float pos=0;
  while (1) {
    memset(buf, 0, BUFF_LEN);
    sock_len = sizeof(clent_addr);
    count = recvfrom(fd, buf, BUFF_LEN, 0, (struct sockaddr*)&clent_addr,
                     &sock_len);  // recvfrom是拥塞函数，没有数据就一直拥塞
    if (count == -1) {
      printf("recieve data fail!\n");
      return;
    }
    char* ipaddr = inet_ntoa(clent_addr.sin_addr);
    //                (clent_addr.sin_addr.s_addr);

    //                ipaddr= inet_ntoa(addr_num);
    //                ipaddr=(char*)addr_num;
    //                strcpy(addr,addr_num);
    printf("IP: %s \n", ipaddr);

//    printf("client:%s\n", buf);  //打印client发过来的信息
    memcpy(udp_frame_recv_ptr_char, buf, UDP_DATA_LENGTH);
    memset(buf, 0, BUFF_LEN);
    printf("pos:%f\n", udp_frame_recv_ptr->position_DownToUp_udp);  //打印自己发送的信息给
    udp_frame_recv_ptr->position_UpToDown_udp=pos;
    sendto(fd, udp_frame_recv_ptr_char, UDP_DATA_LENGTH, 0, (struct sockaddr*)&clent_addr,
           sock_len);  //发送信息给client，注意使用了clent_addr结构体指针
    pos++;
  }
}

/*
    server:
            socket-->bind-->recvfrom-->sendto-->close
*/

int main(int argc, char* argv[]) {
  int server_fd, ret;
  struct sockaddr_in ser_addr;

  server_fd = socket(AF_INET, SOCK_DGRAM, 0);  // AF_INET:IPV4;SOCK_DGRAM:UDP
  if (server_fd < 0) {
    printf("create socket fail!\n");
    return -1;
  }

  memset(&ser_addr, 0, sizeof(ser_addr));
  ser_addr.sin_family = AF_INET;
  ser_addr.sin_addr.s_addr =
      htonl(INADDR_ANY);  // IP地址，需要进行网络序转换，INADDR_ANY：本地地址
  ser_addr.sin_port = htons(SERVER_PORT);  //端口号，需要网络序转换

  ret = bind(server_fd, (struct sockaddr*)&ser_addr, sizeof(ser_addr));
  if (ret < 0) {
    printf("socket bind fail!\n");
    return -1;
  }

  udp_frame_send_ptr = &udp_frame_send;
  udp_frame_recv_ptr = &udp_frame_recv;
  udp_frame_send_ptr_char = (char*)udp_frame_send_ptr;
  udp_frame_recv_ptr_char = (char*)udp_frame_recv_ptr;

  handle_udp_msg(server_fd);  //处理接收到的数据

  // close(server_fd);
  return 0;
}
