cmd_/scratch/jwlemke/2011.09-arm-linux-eabi-lite/obj/linux-2011.09-70-arm-none-linux-gnueabi-i686-pc-linux-gnu/tmp-install/include/rdma/.install := perl scripts/headers_install.pl /scratch/jwlemke/2011.09-arm-linux-eabi-lite/obj/linux-2011.09-70-arm-none-linux-gnueabi-i686-pc-linux-gnu/include/rdma /scratch/jwlemke/2011.09-arm-linux-eabi-lite/obj/linux-2011.09-70-arm-none-linux-gnueabi-i686-pc-linux-gnu/tmp-install/include/rdma arm ib_user_cm.h ib_user_mad.h ib_user_sa.h ib_user_verbs.h rdma_netlink.h rdma_user_cm.h; perl scripts/headers_install.pl /scratch/jwlemke/2011.09-arm-linux-eabi-lite/obj/linux-2011.09-70-arm-none-linux-gnueabi-i686-pc-linux-gnu/include/rdma /scratch/jwlemke/2011.09-arm-linux-eabi-lite/obj/linux-2011.09-70-arm-none-linux-gnueabi-i686-pc-linux-gnu/tmp-install/include/rdma arm ; for F in ; do echo "\#include <asm-generic/$$F>" > /scratch/jwlemke/2011.09-arm-linux-eabi-lite/obj/linux-2011.09-70-arm-none-linux-gnueabi-i686-pc-linux-gnu/tmp-install/include/rdma/$$F; done; touch /scratch/jwlemke/2011.09-arm-linux-eabi-lite/obj/linux-2011.09-70-arm-none-linux-gnueabi-i686-pc-linux-gnu/tmp-install/include/rdma/.install
