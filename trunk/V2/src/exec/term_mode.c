#include <stdio.h>

#include <data>
#include <xfunc>


static void print_buffer(const int len, const char* buffer);
static void print_full_board_line(struct s_data* data, char* buffer);
static void print_empty_board_line(struct s_data* data, char* buffer);
static void print_line(struct s_data* data, const int n, char* buffer);


void printout_game(struct s_data* data)
{
  unsigned int size = data->width * 6 + 2;
  char* buffer = xmalloc((sizeof(*buffer) * size), &(data->status));
  buffer[size - 1] = '\0';
  fwrite("\n", 1, 1, stdout);
  print_full_board_line(data, buffer);
  for (int i = 0; i < data->height; ++i)
    {
      print_empty_board_line(data, buffer);
      print_line(data, i, buffer);
      print_empty_board_line(data, buffer);
      print_full_board_line(data, buffer);
    }
  xfree((void**) &buffer);
}

static void print_buffer(const int len, const char* buffer)
{ fwrite(buffer, len, 1, stdout); fwrite("\n", 1, 1, stdout); }

static void print_full_board_line(struct s_data* data, char* buffer)
{
  for (int i = 0; i < (data->width * 6 + 1); ++i)
    *(buffer + i) = '*';
  print_buffer(data->width * 6 + 1, buffer);
}

static void print_empty_board_line(struct s_data* data, char* buffer)
{
  for (int i = 0; i < data->width; ++i)
    {
      *(buffer + (i * 6)) = '*';
      *(buffer + (i * 6) + 1) = ' ';
      *(buffer + (i * 6) + 2) = ' ';
      *(buffer + (i * 6) + 3) = ' ';
      *(buffer + (i * 6) + 4) = ' ';
      *(buffer + (i * 6) + 5) = ' ';
    }
  print_buffer(data->width * 6 + 1, buffer);
}

static void print_line(struct s_data* data, const int n, char* buffer)
{
  for (int i = 0; i < data->width; ++i)
    {
      *(buffer + 6 * i) = '*';
      *(buffer + 6 * i + 1) = ' ';
      *(buffer + 6 * i + 2) = ' ';
      int pc = game_square_piece(data->g, i, n);
      if (pc >= 0)
	*(buffer + 6 * i + 3) = '0' + pc;
      else
	*(buffer + 6 * i + 3) = ' ';
      *(buffer + 6 * i + 4) = ' ';
      *(buffer + 6 * i + 5) = ' ';
    }
  print_buffer(data->width * 6 + 1, buffer);
}
