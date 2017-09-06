#include "fdf.h"

static void		reset(t_env *mlx)
{
	int			n_y;
	int			n_x;

	t_attr(*matrix)[mlx->matrix_y][mlx->matrix_x];
	matrix = mlx->matrix;
	n_y = -1;
	while (++n_y < mlx->matrix_y && (n_x = -1))
		while (++n_x < mlx->matrix_x)
			COLOR = DEFAULT_COLOR;
	ZOOM = (WIN_W / mlx->matrix_x > WIN_H / mlx->matrix_y ? WIN_H / mlx->matrix_y : \
			WIN_W / mlx->matrix_x);
	POS_X = 100;
	POS_Y = 100;
	ANGLE_X = 0;
	ANGLE_Y = 0;
}

static void		colorise(t_env *mlx, int keycode)
{
	int			n_y;
	int			n_x;
	int			col;

	t_attr(*matrix)[mlx->matrix_y][mlx->matrix_x];
	matrix = mlx->matrix;
	srand(time(NULL));
	col = rand();
	n_y = -1;
	while (++n_y < mlx->matrix_y && (n_x = -1))
		while (++n_x < mlx->matrix_x)
		{
			if (keycode == 49)
				COLOR = (COLOR + col) % 0xffffff + ALT * 42;
			else
				COLOR = (COLOR + rand()) % 0xffffff;
		}
}

static void		position(t_env *mlx, int keycode)
{
	if (keycode == 126)
		POS_Y -= 10;
	if (keycode == 125)
		POS_Y += 10;
	if (keycode == 123)
		POS_X -= 10;
	if (keycode == 124)
		POS_X += 10;
}

static void		alpha(t_env *mlx, int keycode)
{
	if (keycode == 13)
		ANGLE_Y -= 1;
	if (keycode == 1)
		ANGLE_Y += 1;
	if (keycode == 0)
		ANGLE_X -= 1;
	if (keycode == 2)
		ANGLE_X += 1;
	if (keycode == 18)
		mlx->projection = 1;
	if (keycode == 19)
		mlx->projection = 2;
}

int				keys(int keycode, void *param)
{
	cleaner(param);
	if (keycode == 53)
	{
		mlx_destroy_image(((t_env *)param)->mlx_ptr, ((t_env *)param)->img);
		mlx_destroy_window(((t_env *)param)->mlx_ptr, ((t_env *)param)->win);
		exit(1);
	}
	else if ((keycode <= 126) && (keycode >= 123))
		position(param, keycode);
	else if (((keycode >= 0) && (keycode <= 2)) || keycode == 13 || \
			keycode == 18 || keycode == 19)
		alpha(param, keycode);
	else if (keycode == 78)
		unzoom(param);
	else if (keycode == 69)
		zoom(param);
	else if (keycode == 49 || keycode == 48)
		colorise(param, keycode);
	else if (keycode == 51)
		reset(param);
	painter(param);
	return (0);
}