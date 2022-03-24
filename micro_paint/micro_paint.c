#include <unistd.h>
#include <stdio.h>
int	ft_error(FILE *file)
{
	fclose(file);
	return (write(1, "Error: Operation file corrupted\n", 32) && 1);
}
int	ft_check(int w, int h,
		float x_corn, float y_corn, float w_rect, float h_rect)
{
	if (w < x_corn || w > x_corn + w_rect
		|| h < y_corn || h > y_corn + h_rect)
		return (0);
	if (w - x_corn < 1 || x_corn + w_rect - w < 1
		|| h - y_corn < 1 || y_corn + h_rect - h < 1)
		return (2);
	return (1);
}
int	main(int argc, char **argv)
{
	FILE	*file;
	int		width, height, arg, h, w;
	char	backgr, key, symb;
	float	x_corn, y_corn, w_rect, h_rect;
	if (argc != 2)
		return (write(1, "Error: argument\n", 16) && 1);
	file = fopen(argv[1], "r");
	if (!file)
		return (write(1, "Error: Operation file corrupted\n", 32) && 1);
	if (arg = fscanf(file, "%d %d %c\n", &width, &height, &backgr) != 3
		|| (width <= 0 || width > 300 || height <= 0 || height > 300 ))
		return (ft_error(file));
	char	arr[height][width];
	h = -1;
	while (++h < height)
	{
		w = -1;
		while (++w < width)
			arr[h][w] = backgr;
	}
	while ((arg = fscanf(file, "%c %f %f %f %f %c\n",
		&key, &x_corn, &y_corn, &w_rect, &h_rect, &symb)) == 6)
	{
		if ((key != 'r' && key != 'R') || w_rect <= 0 || h_rect <= 0)
			ft_error(file);
		h = -1;
		while (++h < height)
		{
			w = -1;
			while (++w < width)
			{
if ((ft_check(w, h, x_corn, y_corn, w_rect, h_rect) == 2 && key == 'r')
	|| (ft_check(w, h, x_corn, y_corn, w_rect, h_rect) && key == 'R'))
				arr[h][w] = symb;
			}
		}
	}
	if (arg > 0 && arg != 5)
		return (ft_error(file));
	h = -1;
	while (++h < height)
	{
		w = -1;
		while (++w < width)
			write(1, &arr[h][w], 1);
		write(1, "\n", 1);
	}
	return (fclose(file) && 0);
}
