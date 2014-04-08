#include "efm32gg.h"

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/kdev_t.h>
#include <linux/string.h>

MODULE_AUTHOR("asdf");
MODULE_DESCRIPTION("Gamepad driver.");
MODULE_LICENSE("Dual BSD/GPL");

// user program reads from the driver.
static ssize_t gamepad_read(struct file *, char *, size_t, loff_t *);
// user program writes to the driver.
static ssize_t gamepad_write(struct file *, const char *, size_t, loff_t *);
// user program opens the driver.
static int gamepad_open(struct inode *, struct file *);
// user program closes the driver.
static int gamepad_release(struct inode *, struct file *);

static struct file_operations fops = {
    .read = gamepad_read,
    .write = gamepad_write,
    .open = gamepad_open,
    .release = gamepad_release
};

#define DEVICE_NAME "gamepad"

static struct cdev character_device;
static dev_t device_number;

static int device_is_open  = 0; // is device opened by another file?

static void enable_joystick(void)
{
    *GPIO_PC_MODEL  = 0x33333333;
    *GPIO_PC_DOUT   = 0xff;
    *GPIO_EXTIPSELL = 0x22222222;

    *GPIO_EXTIFALL  = 0xff;
    *GPIO_EXTIRISE  = 0xff;

    *GPIO_IEN       = 0xff;
	*GPIO_IFC       = 0xff;
}

// Enable GPIO clock to drive the GPIO outputs.
static void enable_gpio_clock() 
{ 
    *CMU_HFPERCLKEN0 |= CMU2_HFPERCLKEN0_GPIO; 
}

// Enable GPIO output to output current to the LEDs.
static void enable_gpio_led_output()
{
    *GPIO_PA_CTRL = 2;                         /* set high drive strength */
    *GPIO_PA_MODEH = 0x55555555;               /* set pins A8-15 as output */
}

// Function to set up GPIO mode and interrupts.
static void setup_gpio()
{
    enable_gpio_clock();
    //enable_gpio_led_output();
    enable_joystick();
}

// gamepad_init - function to insert this module into kernel space.
// 
// This is the first of two exported functions to handle inserting this
// code into a running kernel
// 
// Returns 0 if successful, otherwise -1

static int __init gamepad_init(void)
{
	setup_gpio();

    int ret = alloc_chrdev_region(&device_number, 0, 1, DEVICE_NAME);
    if (ret < 0) {
        printk(KERN_ALERT "gamepad: failed to allocate major number.\n");
        return ret;
    }
    else {
        printk(KERN_INFO "major number allocated successful");
    }

    int major_number = MAJOR(device_number); // get the major number to this device.
    printk(KERN_INFO "gamepad: major number of our device is %d\n", major_number);
    printk(KERN_INFO "gamepad: to use mknod /dev/%s c %d 0\n", DEVICE_NAME, major_number);

    cdev_init(&character_device, &fops); // The new way used in the compendium.
    int error_code = cdev_add(&character_device, device_number, 1);
    if (error_code < 0) {
        printk(KERN_ALERT "Registering character device failed with %d\n", error_code);
        return error_code;
    }

    // device_number = alloc_chrdev_region();

    // device_class = class_create(THIS_MODULE, "gamepad");
    // device_create = (device_class, NULL, device_number, NULL, "gamepad");

    printk(KERN_ALERT "Hello, world from gamepad driver!\n");

	return 0;
}

// gamepad_exit - function to cleanup this module from kernel space.
// 
// This is the second of two exported functions to handle cleanup this
// code from a running kernel
static void __exit gamepad_exit(void)
{
     // Unregister the device 
     cdev_del(&character_device);
     unregister_chrdev_region(device_number, 1);

	 printk(KERN_ALERT "Goodbye, cruel world... *sad driver exits*\n");
}


// Called when a process tries to open the device file, like
// "cat /dev/mycharfile"
static int gamepad_open(struct inode *inode, struct file *file)
{
    if (device_is_open) {
        printk(KERN_ALERT "device file is already opened by another process!\n");
        return -EBUSY;
    }
    device_is_open++;
	return 0;
}


// Called when a process closes the device file.
static int gamepad_release(struct inode *inode, struct file *file)
{
    device_is_open--;
	return 0;
}

// Called when a process, which already opened the dev file, attempts to read from it.
#define END_OF_FILE 0
static ssize_t gamepad_read(struct file *filp, char *buffer, size_t count, loff_t * offset)
{
    // buf[0] = *GPIO_PC_DIN;
    // buf[1] = 'a';
    // buf[2] = '\n';
    // buf[3] = '\0';
    
    if (*offset >= 4)
        return END_OF_FILE;

    copy_to_user(buffer, *GPIO_PC_DIN, 4);
    *offset += 4;

	return 4;
}
 
// Called when a process writes to dev file: echo "hi" > /dev/hello 
static ssize_t gamepad_write(struct file *filp, const char *buff, size_t count, loff_t * off)
{
	printk(KERN_ALERT "Sorry, this operation isn't supported.\n");
	return -EINVAL;
}

module_init(gamepad_init);
module_exit(gamepad_exit);
