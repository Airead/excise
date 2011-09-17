#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv)
{
  int fd;

  //int open(const char *pathname, int flags);
  if ((fd = open("/dev/fb0", O_RDWR)) < 0)
  {
    fprintf(stderr, "Open framebuffer failed: %s\n", strerror(errno));
    exit(1);
  }

  fprintf(stdout, "Open framebuffer device successfully, fd = %d\n", fd);

  struct fb_var_screeninfo fb_var;

  if (ioctl(fd, FBIOGET_VSCREENINFO, &fb_var) < 0)
  {
    fprintf(stderr, "Cannot get screen info: %s\n", strerror(errno));
    exit(1);
  }

  fprintf(stdout, "X: %d, Y: %d, BPP: %d\n", fb_var.xres, fb_var.yres, fb_var.bits_per_pixel);

  close(fd);

  return 0;
}

// vim:tabstop=8
