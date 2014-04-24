#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

int main(int argc, char *argv[])
{
    int file_descriptor_to_framebuffer = 0;

    // Open fb0 for reading and writing.
    file_descriptor_to_framebuffer = open("/dev/fb0", O_RDWR);
    if (file_descriptor_to_framebuffer == -1) {
        perror("Error: cannot open framebuffer device!");
        exit(1);
    }
    printf("The framebuffer device file was opened successfully!\n");

    // Close fb0 for reading and writing.
    close(file_descriptor_to_framebuffer);

	exit(EXIT_SUCCESS);
}
