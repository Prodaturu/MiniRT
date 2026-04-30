#include "../../include/minirt.h"

static char	*dup_string(const char *src)
{
	size_t	len;
	char	*dst;

	len = strlen(src);
	dst = malloc(len + 1);
	if (dst == NULL)
		return (NULL);
	memcpy(dst, src, len + 1);
	return (dst);
}

static int	count_words(const char *line)
{
	int		count;
	bool	in_word;

	count = 0;
	in_word = false;
	while (*line)
	{
		if (*line == ' ' || *line == '\t' || *line == '\n' || *line == '\r'
			|| *line == '\v' || *line == '\f')
			in_word = false;
		else if (!in_word)
		{
			in_word = true;
			count++;
		}
		line++;
	}
	return (count);
}

char	*trim_in_place(char *str)
{
	char	*end;

	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r'
		|| *str == '\v' || *str == '\f')
		str++;
	if (*str == '\0')
		return (str);
	end = str + strlen(str) - 1;
	while (end > str && (*end == ' ' || *end == '\t' || *end == '\n'
			|| *end == '\r' || *end == '\v' || *end == '\f'))
		*end-- = '\0';
	return (str);
}

char	**split_whitespace(const char *line, int *count)
{
	char	*copy;
	char	*token;
	char	*saveptr;
	char	**tokens;
	int		i;

	*count = count_words(line);
	tokens = calloc((size_t)*count + 1, sizeof(char *));
	copy = dup_string(line);
	if (tokens == NULL || copy == NULL)
		return (free(tokens), free(copy), NULL);
	i = 0;
	token = strtok_r(copy, " \t\r\n\v\f", &saveptr);
	while (token != NULL && i < *count)
	{
		tokens[i] = dup_string(token);
		if (tokens[i] == NULL)
			return (free(copy), free_tokens(tokens), NULL);
		i++;
		token = strtok_r(NULL, " \t\r\n\v\f", &saveptr);
	}
	free(copy);
	return (tokens);
}

static bool	parse_three_parts(const char *str, double *a, double *b, double *c)
{
	char	*copy;
	char	*part;
	char	*saveptr;
	double	values[3];
	int		i;

	copy = dup_string(str);
	if (copy == NULL)
		return (false);
	i = 0;
	part = strtok_r(copy, ",", &saveptr);
	while (part != NULL && i < 3)
	{
		part = trim_in_place(part);
		if (!parse_double_strict(part, &values[i]))
			return (free(copy), false);
		i++;
		part = strtok_r(NULL, ",", &saveptr);
	}
	free(copy);
	if (i != 3 || part != NULL)
		return (false);
	*a = values[0];
	*b = values[1];
	*c = values[2];
	return (true);
}

bool	parse_vec3(const char *str, t_vec *out)
{
	return (parse_three_parts(str, &out->x, &out->y, &out->z));
}

bool	parse_color_rgb(const char *str, t_color *out)
{
	double	r;
	double	g;
	double	b;

	if (!parse_three_parts(str, &r, &g, &b))
		return (false);
	if (r < 0.0 || r > 255.0 || g < 0.0 || g > 255.0 || b < 0.0 || b > 255.0)
		return (false);
	out->r = r / 255.0;
	out->g = g / 255.0;
	out->b = b / 255.0;
	return (true);
}

bool	parse_unit_vec(const char *str, t_vec *out)
{
	double	length;

	if (!parse_vec3(str, out))
		return (false);
	length = vec_length(*out);
	if (length < EPSILON)
		return (false);
	*out = vec_normalize(*out);
	return (true);
}

void	set_error(char *err, size_t size, const char *fmt, ...)
{
	va_list	args;

	if (err == NULL || size == 0)
		return ;
	va_start(args, fmt);
	vsnprintf(err, size, fmt, args);
	va_end(args);
}
