cmd_/scratch/jwlemke/2011.09-arm-linux-eabi-lite/obj/linux-2011.09-70-arm-none-linux-gnueabi-i686-pc-linux-gnu/tmp-install/include/linux/netfilter/ipset/.install := perl scripts/headers_install.pl /scratch/jwlemke/2011.09-arm-linux-eabi-lite/obj/linux-2011.09-70-arm-none-linux-gnueabi-i686-pc-linux-gnu/include/linux/netfilter/ipset /scratch/jwlemke/2011.09-arm-linux-eabi-lite/obj/linux-2011.09-70-arm-none-linux-gnueabi-i686-pc-linux-gnu/tmp-install/include/linux/netfilter/ipset arm ip_set.h ip_set_bitmap.h ip_set_hash.h ip_set_list.h; perl scripts/headers_install.pl /scratch/jwlemke/2011.09-arm-linux-eabi-lite/obj/linux-2011.09-70-arm-none-linux-gnueabi-i686-pc-linux-gnu/include/linux/netfilter/ipset /scratch/jwlemke/2011.09-arm-linux-eabi-lite/obj/linux-2011.09-70-arm-none-linux-gnueabi-i686-pc-linux-gnu/tmp-install/include/linux/netfilter/ipset arm ; for F in ; do echo "\#include <asm-generic/$$F>" > /scratch/jwlemke/2011.09-arm-linux-eabi-lite/obj/linux-2011.09-70-arm-none-linux-gnueabi-i686-pc-linux-gnu/tmp-install/include/linux/netfilter/ipset/$$F; done; touch /scratch/jwlemke/2011.09-arm-linux-eabi-lite/obj/linux-2011.09-70-arm-none-linux-gnueabi-i686-pc-linux-gnu/tmp-install/include/linux/netfilter/ipset/.install
