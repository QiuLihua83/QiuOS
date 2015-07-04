
#include "linux/module.h"
#include "linux/init.h"
#include "linux/kernel.h"
#include "linux/sched.h"
#include "linux/file.h"
#include "linux/kdev_t.h"


static int __init Init(void)
{
    printk(KERN_ALERT "hello qiulihua, initializing now......\n");
    printk(KERN_ALERT "current process is : name=%s, pid=[%i]\n", current->comm, current->pid);
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

