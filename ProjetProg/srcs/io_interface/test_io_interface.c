#include <termios.h>
#include <unistd.h>

#include <io_interface.h>

int main()
{
  struct termios terminfo;
  char	buffer[1];

  save_fd_state(stdin, &terminfo);
  set_fd_raw_mode(stdin);
  read(stdin, buffer, 1);
  if (*buffer == 27)
    printf("read stdin, value : [ESC]\n");
  else
    printf("read stdin, value : [%c]\n", *buffer);
  restore_fd_state(stdin, &terminfo);
  return 0;
}
