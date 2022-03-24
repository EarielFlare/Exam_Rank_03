#include <unistd.h>
#include <stdio.h>
#include <math.h>
int	ft_error(FILE *file)
{
	fclose(file);
	return (write(1, "Error: Operation file corrupted\n", 32) && 1);
}
int	main(int argc, char **argv)
{
	FILE	*file;
	int		width, height, arg, h, w;
	char	backgr, key, symb;
	float	x_cntr, y_cntr, radius, dist;
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
	while ((arg = fscanf(file, "%c %f %f %f %c\n",
		&key, &x_cntr, &y_cntr, &radius, &symb)) == 5)
	{
		if ((key != 'c' && key != 'C') || radius <= 0)
			ft_error(file);
		h = -1;
		while (++h < height)
		{
			w = -1;
			while (++w < width)
			{
				dist = sqrt(pow(h - y_cntr, 2) + pow(w - x_cntr, 2));
				if (dist <= radius)
					if ((key == 'c' && radius - dist < 1) || (key == 'C'))
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
