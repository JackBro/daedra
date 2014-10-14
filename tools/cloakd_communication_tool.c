/*
 * This tool helps you communicate with cloakd module
 * NOTE: dependency on libnl3
 */

//#include <netlink/socket.h>
//#include <netlink/genl/genl.h>
#include <linux/genetlink.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#define NETLINK_USER    31
#define PAYLOAD_SIZE    64 // TODO: Make this dynamic 

struct sockaddr_nl src_addr, dest_addr;
struct nlmsghdr *nlh = NULL;
struct iovec iov;
struct msghdr msg;


int main(void)
{
    int sock_fd;
    sock_fd = socket(PF_NETLINK, SOCK_RAW, NETLINK_USER);
    if (sock_fd < 0)
    {
        fprintf(stderr, "Can't open socket");
        return -1;
    }

    memset(&src_addr, 0, sizeof(src_addr));
    src_addr.nl_family = AF_NETLINK;
    src_addr.nl_pid = getpid(); /* self pid */

    bind(sock_fd, (struct sockaddr *)&src_addr, sizeof(src_addr));

    memset(&dest_addr, 0, sizeof(dest_addr));

    dest_addr.nl_family = AF_NETLINK;
    dest_addr.nl_pid = 0; /* For Linux Kernel */
    dest_addr.nl_groups = 0; /* unicast */

    nlh = (struct nlmsghdr *)malloc(NLMSG_SPACE(PAYLOAD_SIZE));
    memset(nlh, 0, NLMSG_SPACE(PAYLOAD_SIZE));
    nlh->nlmsg_len = NLMSG_SPACE(PAYLOAD_SIZE);
    nlh->nlmsg_pid = getpid();
    nlh->nlmsg_flags = 0;

    unsigned char payload[1] = {0x01};
    //strcpy(NLMSG_DATA(nlh), "Hello");
    memcpy(NLMSG_DATA(nlh), payload, 1);

    iov.iov_base = (void *)nlh;
    iov.iov_len = nlh->nlmsg_len;
    msg.msg_name = (void *)&dest_addr;
    msg.msg_namelen = sizeof(dest_addr);
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;

    printf("Sending message to kernel. Our pid=%d\n", getpid());
    sendmsg(sock_fd, &msg, 0);
    //printf("Waiting for message from kernel\n");

    /* Read message from kernel */
    /*
    recvmsg(sock_fd, &msg, 0);
    printf("Received message payload: %s\n", NLMSG_DATA(nlh));
    close(sock_fd);
    */
}
