#include <linux/fs.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "bees"


static int dev_open(struct inode*, struct file*);
static int dev_release(struct inode*, struct file*);

static ssize_t dev_read(struct file*, char*, size_t, loff_t*);
static ssize_t dev_write(struct file*, const char*, size_t, loff_t*);


//	fops			fops
static struct file_operations fops = {
	.open = dev_open,
	.read = dev_read,
	.write = dev_write,
	.release = dev_release,
};
// fops


static int major;


// do NOT use british github copilot what the fuck is __innit
static int __init bees_innit(void) 
{
	major = register_chrdev(0, DEVICE_NAME, &fops); // fops
	
	if (major < 0) {
		printk(KERN_ALERT "your house will fucking explode in 3 seconds\n");
		return major;
	}

	printk(KERN_INFO "bees loaded; %d\n", major);
	return 0;
}




static void __exit bees_cleanup(void) {
	unregister_chrdev(major, DEVICE_NAME);
    	printk(KERN_INFO "bees gone\n");
}





static int dev_open(struct inode *inodep, struct file *filep) {
	printk(KERN_INFO "the bees are being shaken\n");
	return 0;
}


static ssize_t dev_write(struct file *filep, const char *buffer, size_t len, loff_t *offset) {
	printk(KERN_INFO "dont do that (bees are read only)\n");
	return -EFAULT; // curse of ra
}

static int dev_release(struct inode *inodep, struct file *filep) {
	printk(KERN_INFO "bees sealed");
	return 0;
}

static ssize_t dev_read(struct file *filep, char *buffer, size_t len, loff_t *offset) {
	int errors = 0;
	char *message = "z"; 
	int message_len = strlen(message);

	errors = copy_to_user(buffer, message, message_len);
	return errors == 0 ? message_len : -EFAULT;
}



// i have a final in 47 hours
module_init(bees_innit);
module_exit(bees_cleanup);

// this needs to be here or this doesnt like compile at all
MODULE_LICENSE("CC0");
