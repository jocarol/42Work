#include "fractol.h"
#include <stdio.h>

static void					put_pixel(t_env *z, int x, int y, int color)
{
  int					i;

  if (x >= IMG_SIZE || y >= IMG_SIZE || x < 0 || y < 0)
    return ;
  i = z->linesize * y + x * (z->bpp / 8);
  z->data[i] = color & 0xff;
  z->data[++i] = color >> 8 & 0xff;
  z->data[++i] = color >> 16;
}

static void 					fractol(t_env *z, int x, int y)
{
  double      zr_tmp;
	double			p_check;
  int         iteration;

	p_check = sqrt((x - 0.25) * (x - 0.25) + y * y);
	if (x < (p_check - 2 * (p_check * p_check) + 0.25))
	{
		put_pixel(z, x, y, 0x00FFFFFF);
		return;
	}
	iteration = 0;
  while (z->r * z->r + z->i * z->i < 4 && iteration < z->iteration)
  {
    zr_tmp = z->r;
    z->r = z->r * z->r - z->i * z->i + z->c_r;
		if (z->frac_type == BURNINGSHIP)
			z->i = 2 * fabs(z->i * zr_tmp) + z->c_i;
		else
			z->i = 2 * z->i * zr_tmp + z->c_i;
    iteration++;
  }
	if (iteration == z->iteration)
		put_pixel(z, x, y, 0x00FFFFFF);
	else
		put_pixel(z, x, y, (0x00FFFFFF / 260 * (iteration + z->col)));
}

static void					display_info(t_env *z)
{
	if (z->display_info)
	{
	 	mlx_string_put(z->mlx_ptr, z->win, 20, 725, 0x00000000, "Fractal       : ");
	 	if (z->frac_type == 1)
	   	mlx_string_put(z->mlx_ptr, z->win, 195, 725, 0x00000000, "Mandlebrot");
	 	else if (z->frac_type == 2)
	   	mlx_string_put(z->mlx_ptr, z->win, 195, 725, 0x00000000, "Julia");
	 	else if (z->frac_type == 3)
	   	mlx_string_put(z->mlx_ptr, z->win, 195, 725, 0x00000000, "Burning Ship");
	 	mlx_string_put(z->mlx_ptr, z->win, 20, 745, 0x00000000, "Zoom          : ");
	 	mlx_string_put(z->mlx_ptr, z->win, 195, 745, 0x00000000, ft_itoa(z->zoom));
	 	mlx_string_put(z->mlx_ptr, z->win, 20, 765, 0x00000000, "Itération(s)   : ");
	 	mlx_string_put(z->mlx_ptr, z->win, 195, 765, 0x00000000, ft_itoa(z->iteration));
	}
}

void            *th_bp(void *z)
{
  t_env         *env_tmp;
  int           x;
  int           y;

  // tmp_env = (t_env *)z;
  env_tmp = (t_env *)malloc(sizeof(t_env *));

  x = -1;
  while (++x < IMG_SIZE)
  {
    y = -1;
    while (++y < IMG_SIZE)
    {
      if (z->frac_type == JULIA)
      {
        env_tmp->r = x / env_tmp->zoom + env_tmp->x1;
        env_tmp->i = y / env_tmp->zoom + env_tmp->y1;
      }
      else
      {
        env_tmp->c_r = env_tmp->x / env_tmp->zoom + env_tmp->x1;
        env_tmp->c_i = env_tmp->y / env_tmp->zoom + env_tmp->y1;
        env_tmp->r = 0.0;
        env_tmp->i = 0.0;
      }
      fractol(z, x, y);
    }
  }

}


void 						*draw(t_env *z)
{
  mlx_put_image_to_window(z->mlx_ptr, z->win, z->img, 0, 0);
  display_info(z);
}