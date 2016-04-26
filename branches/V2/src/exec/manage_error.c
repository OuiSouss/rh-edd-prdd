#include <stdio.h>

#include <data>
#include <error_flags>

static void usage(const char* name);
static void format();

/**
 * @fn void manage_error (struct s_data* data)
 * @brief Function used to provide backup informations to
 * the user when an error occur.
 * @param[in] data A pointer to the program data.
 */
void manage_error(struct s_data* data)
{
  if (data->status == WRONG_USAGE_ERROR)
    usage(data->av[0]);
  else
    {
      fprintf(stderr, "A critical error occured : ");
      switch (data->status)
	{
	case ALLOC_ERROR :
	  fprintf(stderr, "the program was unable to allocate enough memory\n");
	  break;
	case OPT_ERROR :
	  fprintf(stderr, "at least one option was not recognised properly\n");
	  usage(data->av[0]);
	  break;
	case TERM_GUI_ERROR :
	  fprintf(stderr, "multiple output options specified\n");
	  usage(data->av[0]);
	  break;
	case IOCTL_TERM_ERROR :
	  fprintf(stderr, "conflict between output mode and terminal control mode\n");
	  usage(data->av[0]);
	  break;
	case SOLVER_GAME_ERROR :
	  fprintf(stderr, "conflict between game modes requested\n");
	  usage(data->av[0]);
	  break;
	case FILE_INPUT_ERROR :
	  fprintf(stderr, "wrong input file format\n");
	  format();
	  usage(data->av[0]);
	  break;
	case FILE_ACCESS_ERROR :
	  fprintf(stderr, "unable to open input file\n");
	  break;
	case MULTIPLE_SIZE_ERROR :
	  fprintf(stderr, "too many sizes specified as options\n");
	  break;
	}
    }
}

/**
 * @fn static void usage (const char* name)
 * @brief Local call that will tell the user how to properly call the program.
 * @param[in] name A pointer to the field associated with the call path of the program.
 */
static void usage(const char* name)
{
  fprintf(stderr, "usage : %s -f <path-to-file> -w <size> -h <size> -{g/t/s} -i\n", name);
  fprintf(stderr, "-w and -h flags must occur only once.\n");
  fprintf(stderr, "Only one the flags between -g, -t and -s must appear.\n");
  fprintf(stderr, "-i requires -t to work properly.\n");
}

/**
 * @fn static void format()
 * @brief Local function used to tell the user how should look the input configuration file.
 */
static void format()
{
  fprintf(stderr, "Input file format :\n");
  fprintf(stderr, "x, y, width, height, move_x, move_y\n");
  fprintf(stderr, "where x and y are the lowest coordinates of the piece,\n");
  fprintf(stderr, "width and height the dimensions of the piece\n");
  fprintf(stderr, "and move_x/move_y either 0 or 1 depending if the piece can move or not for the associated direction.\n");
}
