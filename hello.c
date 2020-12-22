#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>

#include <linux/ktime.h>
#include <linux/slab.h>

struct head_list {
struct head_list *next;
ktime_t time;
};

MODULE_AUTHOR("Pavlo Ivashchenko IV-82");
MODULE_DESCRIPTION("Lab6");
MODULE_LICENSE("Dual BSD/GPL");

static struct head_list *head;

static int repeat = 1;
module_param(repeat, uint, 0444);
MODULE_PARM_DESC(repeat, "Repeat amount of printing hello world");

static int __init thisinit(void)
{
uint i;

struct head_list *var_1, *var_2;

head = kmalloc(sizeof(struct head_list *), GFP_KERNEL);

var_1 = head;
if (repeat == 0) {
	pr_warn("Entered parameter equals 0");
} else if (repeat >= 5 && repeat <= 10) {
	pr_warn("Entered parameter is between 5 and 10");
} else if (repeat > 10) {
	pr_warn("Entered parameter is bigger than 10");
return -EINVAL;
}

for (i = 0; i < repeat; i++) {
	var_1->next = kmalloc(sizeof(struct head_list), GFP_KERNEL);
	var_1->time = ktime_get();
	pr_info("Hello World!");
	var_2 = var_1;
	var_1 = var_1->next;
}

if (repeat != 0) {
	kfree(var_2->next);
	var_2->next = NULL;
}

pr_info("Repeat: %d\n", repeat);

return 0;
}

static void __exit thisexit(void)
{
struct head_list *var;

while (head != NULL && repeat != 0) {
	var = head;
	pr_info("Time: %lld", var->time);
	head = var->next;
	kfree(var);
}
pr_info("");
}

module_init(thisinit);
module_exit(thisexit);
