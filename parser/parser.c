#include "../include/minirt.h"

static int	parse_line(char *line, t_scene *scene, char *err, size_t size)
{
	char	**tokens;
	int		count;
	int		ok;

	line = trim_in_place(line);
	if (*line == '\0' || *line == '#')
		return (1);
	tokens = split_whitespace(line, &count);
	if (tokens == NULL)
		return (set_error(err, size, "memory allocation failed while parsing"), 0);
	ok = 0;
	if (count > 0 && strcmp(tokens[0], "A") == 0)
		ok = parse_ambient(tokens, count, scene, err, size);
	else if (count > 0 && strcmp(tokens[0], "R") == 0)
		ok = parse_resolution(tokens, count, scene, err, size);
	else if (count > 0 && (strcmp(tokens[0], "c") == 0
			|| strcmp(tokens[0], "C") == 0))
		ok = parse_camera(tokens, count, scene, err, size);
	else if (count > 0 && (strcmp(tokens[0], "l") == 0
			|| strcmp(tokens[0], "L") == 0))
		ok = parse_light(tokens, count, scene, err, size);
	else if (count > 0 && strcmp(tokens[0], "sp") == 0)
		ok = parse_sphere(tokens, count, scene, err, size);
	else if (count > 0 && strcmp(tokens[0], "pl") == 0)
		ok = parse_plane(tokens, count, scene, err, size);
	else if (count > 0 && strcmp(tokens[0], "cy") == 0)
		ok = parse_cylinder(tokens, count, scene, err, size);
	else if (count > 0 && strcmp(tokens[0], "sq") == 0)
		ok = parse_square(tokens, count, scene, err, size);
	else if (count > 0 && strcmp(tokens[0], "tr") == 0)
		ok = parse_triangle(tokens, count, scene, err, size);
	else
		set_error(err, size, "unknown identifier: %s", tokens[0]);
	free_tokens(tokens);
	return (ok);
}

int	parse_scene_file(const char *path, t_scene *scene, char *err, size_t size)
{
	FILE	*fp;
	char	*line;
	size_t	cap;
	ssize_t	read_len;
	int		line_no;

	memset(scene, 0, sizeof(*scene));
	fp = fopen(path, "r");
	if (fp == NULL)
		return (set_error(err, size, "failed to open scene file"), 0);
	line = NULL;
	cap = 0;
	line_no = 0;
	read_len = getline(&line, &cap, fp);
	while (read_len != -1)
	{
		line_no++;
		if (!parse_line(line, scene, err, size))
			return (free(line), fclose(fp), set_error(err, size,
					"line %d: %s", line_no, err), 0);
		read_len = getline(&line, &cap, fp);
	}
	free(line);
	fclose(fp);
	return (1);
}
