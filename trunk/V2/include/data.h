#ifndef _DATA_H
# define _DATA_H

# include <game.h>

# ifndef _S_DATA
#  define _S_DATA

struct s_data
{
	int ac;
	char** av;

	int status;
	int* flags;

	int index;

	int width;
	int height;

	piece* pcs;
	int nb_pcs;

	game g;

	bool (*game_over)(cgame);
};

# endif /* _S_DATA */

# ifndef _T_STATUS
#  define _T_STATUS

# define START_STATUS 1
# define END_STATUS 0

# endif /* _T_STATUS */

# define BUFFER_SIZE 64
# define MAX_PIECES 10

void init_data(struct s_data* data, int* argc, char** argv, bool (*game_over)(cgame));
void delete_data(struct s_data* data);

#endif /* _DATA_H */
