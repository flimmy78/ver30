cmd_/scratch/jwlemke/2011.09-arm-linux-eabi-lite/obj/linux-2011.09-70-arm-none-linux-gnueabi-i686-pc-linux-gnu/tmp-install/include/linux/nfsd/.install := perl scripts/headers_install.pl /scratch/jwlemke/2011.09-arm-linux-eabi-lite/obj/linux-2011.09-70-arm-none-linux-gnueabi-i686-pc-linux-gnu/include/linux/nfsd /scratch/jwlemke/2011.09-arm-linux-eabi-lite/obj/linux-2011.09-70-arm-none-linux-gnueabi-i686-pc-linux-gnu/tmp-install/include/linux/nfsd arm const.h debug.h export.h nfsfh.h stats.h syscall.h; perl scripts/headers_install.pl /scratch/jwlemke/2011.09-arm-linux-eabi-lite/obj/linux-2011.09-70-arm-none-linux-gnueabi-i686-pc-linux-gnu/include/linux/nfsd /scratch/jwlemke/2011.09-arm-linux-eabi-lite/obj/linux-2011.09-70-arm-none-linux-gnueabi-i686-pc-linux-gnu/tmp-install/include/linux/nfsd arm ; for F in ; do echo "\#include <asm-generic/$$F>" > /scratch/jwlemke/2011.09-arm-linux-eabi-lite/obj/linux-2011.09-70-arm-none-linux-gnueabi-i686-pc-linux-gnu/tmp-install/include/linux/nfsd/$$F; done; touch /scratch/jwlemke/2011.09-arm-linux-eabi-lite/obj/linux-2011.09-70-arm-none-linux-gnueabi-i686-pc-linux-gnu/tmp-install/include/linux/nfsd/.install