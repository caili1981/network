
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <sys/queue.h>
#include <stdarg.h>
#include <errno.h>
#include <getopt.h>

#include <netinet/in.h>
#include <net/if.h>
#ifdef RTE_EXEC_ENV_LINUXAPP
#include <linux/if_tun.h>
#endif
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <signal.h>

#include <rte_common.h>
#include <rte_log.h>
#include <rte_memory.h>
#include <rte_memcpy.h>
#include <rte_eal.h>
#include <rte_per_lcore.h>
#include <rte_launch.h>
#include <rte_atomic.h>
#include <rte_lcore.h>
#include <rte_branch_prediction.h>
#include <rte_interrupts.h>
#include <rte_debug.h>
#include <rte_ether.h>
#include <rte_ethdev.h>
#include <rte_mempool.h>
#include <rte_mbuf.h>
#include <rte_string_fns.h>
#include <rte_cycles.h>
#include <rte_pdump.h>

static int tap_create(char *name)
{
    struct ifreq ifr;
    int fd, ret;

    fd = open("/dev/net/tun", O_RDWR);
    if (fd < 0) {
        printf("open tun ifp failed\n");
        return fd;
    }

    memset(&ifr, 0, sizeof(ifr));

    /* TAP device without packet information */
    ifr.ifr_flags = IFF_TAP | IFF_NO_PI;

    if (name && *name)
        snprintf(ifr.ifr_name, IFNAMSIZ, "%s", name);

    ret = ioctl(fd, TUNSETIFF, (void *) &ifr);
    if (ret < 0) {
        close(fd);
        return ret;
    }

    if (name)
        snprintf(name, IFNAMSIZ, "%s", ifr.ifr_name);
    printf("tap_create %s\n", name);

    return fd;
}

int
main(void)
{
    int fd;
    char buf[1000];
    ssize_t len;
    char tap_name[100] = "my_test_tap_server";
    fd = tap_create(tap_name);
    printf("echo from client:\n");
    while (1) {
        len = read(fd, buf, 50);
        if (len == -1 || len == 0) {
            sleep(1);
        }
        printf("[%5ld:]%s\n", len, buf);
    }
    return 0;
}
