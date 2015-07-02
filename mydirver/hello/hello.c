
#include "linux/module.h"
#include "linux/init.h"
#include "linux/kernel.h"


static int __init Init(void)
{
    printk(KERN_ALERT "hello qiulihua, initializing now......\n");

    return 0;
}

static void __exit Exit(void)
{
    printk(KERN_ALERT "hello qiulihua, exit now, bye bye !\n");
}


module_init(Init);
module_exit(Exit);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("MelodyQiu");
MODULE_DESCRIPTION("This is a simple for drivers program.hello !");

