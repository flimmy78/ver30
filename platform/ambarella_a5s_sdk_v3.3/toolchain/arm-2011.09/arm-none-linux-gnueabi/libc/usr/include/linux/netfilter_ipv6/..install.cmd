cmd_/scratch/jwlemke/2011.09-arm-linux-eabi-lite/obj/linux-2011.09-70-arm-none-linux-gnueabi-i686-pc-linux-gnu/tmp-install/include/linux/netfilter_ipv6/.install := perl scripts/headers_install.pl /scratch/jwlemke/2011.09-arm-linux-eabi-lite/obj/linux-2011.09-70-arm-none-linux-gnueabi-i686-pc-linux-gnu/include/linux/netfilter_ipv6 /scratch/jwlemke/2011.09-arm-linux-eabi-lite/obj/linux-2011.09-70-arm-none-linux-gnueabi-i686-pc-linux-gnu/tmp-install/include/linux/netfilter_ipv6 arm ip6_tables.h ip6t_HL.h ip6t_LOG.h ip6t_REJECT.h ip6t_ah.h ip6t_frag.h ip6t_hl.h ip6t_ipv6header.h ip6t_mh.h ip6t_opts.h ip6t_rt.h; perl scripts/headers_install.pl /scratch/jwlemke/2011.09-arm-linux-eabi-lite/obj/linux-2011.09-70-arm-none-linux-gnueabi-i686-pc-linux-gnu/include/linux/netfilter_ipv6 /scratch/jwlemke/2011.09-arm-linux-eabi-lite/obj/linux-2011.09-70-arm-none-linux-gnueabi-i686-pc-linux-gnu/tmp-install/include/linux/netfilter_ipv6 arm ; for F in ; do echo "\#include <asm-generic/$$F>" > /scratch/jwlemke/2011.09-arm-linux-eabi-lite/obj/linux-2011.09-70-arm-none-linux-gnueabi-i686-pc-linux-gnu/tmp-install/include/linux/netfilter_ipv6/$$F; done; touch /scratch/jwlemke/2011.09-arm-linux-eabi-lite/obj/linux-2011.09-70-arm-none-linux-gnueabi-i686-pc-linux-gnu/tmp-install/include/linux/netfilter_ipv6/.install