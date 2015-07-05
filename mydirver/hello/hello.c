
#include "linux/module.h"
#include "linux/init.h"
#include "linux/kernel.h"
#include "linux/sched.h"
#include "linux/file.h"
#include "linux/kdev_t.h"
#include "linux/fs.h"
#include "linux/fcntl.h"
#include "linux/cdev.h"


void initDev(void);
void releaseDev(void);
ssize_t hello_read(struct file *pfile, char __user *buffer, size_t count, loff_t * offp);
ssize_t hello_write(struct file *pfile, const char __user *buffer, size_t count, loff_t * offp);
int hello_open(struct inode * inode, struct file * pfile);
int hello_release(struct inode * inode, struct file * pfile);

const unsigned int DEV_NUM = 1;

static  dev_t  mydev;
struct  cdev   mycdev;


struct file_operations hello_ops = {
    .owner = THIS_MODULE,
    .open  = hello_open,
    .release = hello_release,
    .read  = hello_read,
    .write = hello_write,
};




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

ssize_t hello_read(struct file *pfile, char __user *buffer, size_t count, loff_t * offp)
{

    printk(KERN_ALERT "you are reading data....\n");

    return 0;
}

ssize_t hello_write(struct file *pfile, const char __user *buffer, size_t count, loff_t * offp)
{
    printk(KERN_ALERT "you are writing data....");

    return 0;
}

int hello_open(struct inode * inode, struct file * pfile)
{
    printk(KERN_ALERT "you are opening file....");

    return 0;
}

int hello_release(struct inode * inode, struct file * pfile)
{
    printk(KERN_ALERT "you are releazing file....");

    return 0;
}



module_init(Init);
module_exit(Exit);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("MelodyQiu");
MODULE_DESCRIPTION("This is a simple for drivers program.hello !");

