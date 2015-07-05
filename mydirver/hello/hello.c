
#include "linux/module.h"
#include "linux/init.h"
#include "linux/kernel.h"
#include "linux/sched.h"
#include "linux/file.h"
#include "linux/kdev_t.h"
#include "linux/fs.h"
#include "linux/fcntl.h"
#include "linux/cdev.h"

const unsigned int DEV_NUM = 1;

static  dev_t  mydev;
struct  cdev   mycdev;


struct file_operations hello_ops = {
    .owner = THIS_MODULE,
};

void initDev(void);
void releaseDev(void);

static int __init Init(void)
{
    printk(KERN_ALERT "hello qiulihua, initializing now......\n");
    printk(KERN_ALERT "current process is : name=%s, pid=[%i]\n", current->comm, current->pid);
   
   initDev(); 
    return 0;
}

void initDev(void)
{
    int ret = 0;
    ret = alloc_chrdev_region(&mydev, 0, DEV_NUM, "hellodev");
    if(0 == ret)
    {
         printk(KERN_ALERT "init dev succed! major=%i, minor=%i\n", MAJOR(mydev),MINOR(mydev));   
    }
   else
    {
        printk(KERN_ALERT "init failed! ret = %i, now give up.\n", ret);
        return;
    }

    cdev_init(&mycdev, &hello_ops);
    mycdev.owner = THIS_MODULE;
    
    ret = cdev_add(&mycdev, mydev, DEV_NUM);
    if(0 == ret)
    {
        printk(KERN_ALERT "cdev adding succed!\n");
    }
    else
    {
        printk(KERN_ALERT "cdev adding failed! ret = %i. now give up.\n", ret);
        return;
    }  
    return;
}

void releaseDev(void)
{
    cdev_del(&mycdev);
    unregister_chrdev_region(mydev, DEV_NUM);
}


static void __exit Exit(void)
{
    releaseDev();
    printk(KERN_ALERT "hello qiulihua, exit now, bye bye !\n");
}


module_init(Init);
module_exit(Exit);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("MelodyQiu");
MODULE_DESCRIPTION("This is a simple for drivers program.hello !");

