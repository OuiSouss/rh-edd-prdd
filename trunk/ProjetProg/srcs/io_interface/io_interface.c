#include <termios.h>
#include <unistd.h>

#include <io_interface.h>

void save_fd_state(int fd, void* ptr)
{
  struct termios* terminfo = ptr;

  if (terminfo != NULL)
    tcgetattr(fd, terminfo);
}

void restore_fd_state(int fd, void* ptr)
{
  struct termios* terminfo = ptr;

  if (terminfo != NULL)
    tcsetattr(fd, TCSANOW, terminfo);
}

void set_fd_raw_mode(int fd)
{
  struct termios terminfo;

  tcgetattr(fd, &terminfo);
  terminfo.c_lflag &= ~ICANON;
  terminfo.c_lflag &= ~ECHO;
  terminfo.c_cc[VMIN] = 1;
  terminfo.c_cc[VTIME] = 0;
  tcsetattr(fd, TCSANOW, &terminfo);
}

void unset_fd_raw_more(int fd)
{
  struct termios terminfo;

  tcgetattr(fd, &terminfo);
  terminfo.c_lflag &= ICANON;
  terminfo.c_lflag &= ECHO;
  terminfo.c_cc[VMIN] = 0;
  terminfo.c_cc[VTIME] = 0;
  tcsetattr(fd, TCSANOW, &terminfo);
}
