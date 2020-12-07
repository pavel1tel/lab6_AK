#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/printk.h>

MODULE_AUTHOR("Ivashchenko Pavlo");
MODULE_DESCRIPTION("Hello world printing Linux module");
MODULE_LICENSE("Dual BSD/GPL");

static int repeat = 1;
module_param(repeat, uint, S_IRUGO);
MODULE_PARM_DESC(times, "repeat amount");

static int __init hello_init(void)
{
    uint i = 0;
    if(repeat == 0) {
        printk(KERN_WARNING "Repeat parameter equals 0");  
    } else if(repeat >= 5 && repeat <= 10) {
        printk(KERN_WARNING "Repeat parameter is between 5 and 10");
    } else if(repeat > 10) {
        printk(KERN_ERR "Repeat parameter is bigger than 10");
        return -EINVAL;
    }
    for(i = 0; i < repeat; i++) {
        printk(KERN_EMERG "Hello, world!\n");
    }
    printk(KERN_INFO "Repeat: %d\n", repeat);
    return 0;
}

static void __exit hello_exit(void)
{
    /* Do nothing here right now */
}

module_init(hello_init);
module_exit(hello_exit);
