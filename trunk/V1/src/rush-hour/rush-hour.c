#include <rush-hour>

#include <exec>
#include <game.h>

int main(int argc, char** argv)
{
  struct s_exec data_set;

  init_exec(&data_set, argc, (const char**) argv);
  while (data_set.status == 0)
    loop_exec(&data_set);
  end_exec(&data_set);
  return data_set.status;
}
