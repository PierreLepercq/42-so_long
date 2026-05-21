#include <unistd.h>
#include <mlx.h>

int	quit_game(int game)
{
	(void)game;
	write(1, "test", 4);
	return (0);
}

int	main(void)
{
	void	*mlx;
	void	*win;
	int		game;

	game = 42;
	mlx = mlx_init();
	win = mlx_new_window(mlx, 400, 300, "ISSUE");
	mlx_hook(win, 17, 0, quit_game, &game);
	mlx_loop(mlx);
	return (0);
}
