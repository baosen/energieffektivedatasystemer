#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>

struct pixel {              // EFM32GG uses 16-bit RGB565 format for each pixel. Raspberry Pi does that too!
    unsigned int blue  : 5; // flipped because little-endian machine.
    unsigned int green : 6;
    unsigned int red   : 5;
};

int      framebuffer_file_descriptor = 0;
struct   fb_var_screeninfo var_info;
char*    framebuffer_ptr             = NULL;
long int screen_size                 = 0;

int initialize_renderer()
{
    struct fb_fix_screeninfo fix_info;

    // Open framebuffer file fb0.
    framebuffer_file_descriptor = open("/dev/fb0", O_RDWR);
    if (framebuffer_file_descriptor == -1) {
        printf("Error: cannot open framebuffer device.\n");
        return -1;
    }
    printf("The framebuffer device file has been successfully opened.\n");

    // Get fixed screen information.
    if (ioctl(framebuffer_file_descriptor, FBIOGET_FSCREENINFO, &fix_info)) {
        close(framebuffer_file_descriptor);
        printf("Error: Failed to read fixed screen information.\n");
        return -1;
    }

    // Get variable screen information.
    if (ioctl(framebuffer_file_descriptor, FBIOGET_VSCREENINFO, &var_info)) {
        close(framebuffer_file_descriptor);
        printf("Error: Failed to read variable screen information.\n");
        return -1;
    }
    printf("Display info %dx%d, %d bpp\n",
            var_info.xres, var_info.yres,
            var_info.bits_per_pixel);

    screen_size = fix_info.smem_len;

    // Map framebuffer to user memory.
    framebuffer_ptr = (char*)mmap(0, screen_size, PROT_READ | PROT_WRITE, MAP_SHARED, framebuffer_file_descriptor, 0);

    if ((int)framebuffer_file_descriptor == -1) {
        printf("Error: Failed to mmap framebuffer.\n");
        return -1;
    }

    return 0;
}

void deinitialize_renderer()
{
    // Free resources.
    munmap(framebuffer_ptr, screen_size);
    close(framebuffer_file_descriptor);
}

void draw_pixel_at_position(int x, int y, unsigned int red, unsigned int green, unsigned int blue)
{
    ((struct pixel*)(framebuffer_ptr + (y * (var_info.xres * var_info.bits_per_pixel / 8)) + (x * (var_info.bits_per_pixel / 8))))->red   = red;
    ((struct pixel*)(framebuffer_ptr + (y * (var_info.xres * var_info.bits_per_pixel / 8)) + (x * (var_info.bits_per_pixel / 8))))->green = green;
    ((struct pixel*)(framebuffer_ptr + (y * (var_info.xres * var_info.bits_per_pixel / 8)) + (x * (var_info.bits_per_pixel / 8))))->blue  = blue;
}

void fill_screen_with_color(unsigned red, unsigned int green, unsigned int blue) 
{
    for (int index = 0; index < screen_size; index += (var_info.bits_per_pixel / 8)) {
        ((struct pixel*)(framebuffer_ptr + index))->red   = red;
        ((struct pixel*)(framebuffer_ptr + index))->green = green;
        ((struct pixel*)(framebuffer_ptr + index))->blue  = blue;
    }
}

int main(int argc, char* argv[])
{
    // memset(framebuffer_ptr, 0x0f, screen_size / 2);                   // Fill the upper half of the screen with light green color!
    // memset(framebuffer_ptr + screen_size / 2, 0x18, screen_size / 2); // and the lower half with blue color!
    // memset(framebuffer_ptr, 0xFF, var_info.xres * (var_info.bits_per_pixel / 8));
    
    // for (int i = 0; i < var_info.xres * (var_info.bits_per_pixel / 8); i += 2) {
    //     ((struct pixel*)(framebuffer_ptr + i))->red   = 31;
    //     ((struct pixel*)(framebuffer_ptr + i))->green = 0;
    //     ((struct pixel*)(framebuffer_ptr + i))->blue  = 0;
    // }
    // for (int i = 0; i < var_info.xres; i++) {
    //     draw_pixel_at_position(i, 100, 31, 0, 0);
    // }
    
    
    //memset(framebuffer_ptr + var_info.xres * 24, 0xFF, var_info.xres * 2);

    if (initialize_renderer() == -1) {
        return -1;
    }
    fill_screen_with_color(0, 0, 31);
    // for (int j = 10; j < 100; j++) {
    //     for (int i = 10; i < 100; i++) {
    //         draw_pixel_at_position(i, j, 31, 0, 0);
    //     }
    // }
    deinitialize_renderer();

    return EXIT_SUCCESS;
}
