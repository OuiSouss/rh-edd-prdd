#ifndef _IO_INTERFACE_H
# define _IO_INTERFACE_H

#  define stdin 0
#  define stdout 1
#  define stderr 2

void save_fd_state(int fd, void* ptr);

void restore_fd_state(int fd, void* ptr);

void set_fd_raw_mode(int fd);

void unset_fd_raw_mode(int fd);

#endif /* _IO_INTERFACE_H */
