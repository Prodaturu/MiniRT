#include "../../include/minirt.h"

bool	parse_double_strict(const char *str, double *out)
{
	char	*end;
	double	value;

	if (str == NULL || *str == '\0')
		return (false);
	errno = 0;
	value = strtod(str, &end);
	if (errno != 0 || end == str || *end != '\0')
		return (false);
	*out = value;
	return (true);
}

bool	parse_int_strict(const char *str, int *out)
{
	char	*end;
	long	value;

	if (str == NULL || *str == '\0')
		return (false);
	errno = 0;
	value = strtol(str, &end, 10);
	if (errno != 0 || end == str || *end != '\0' || value < -2147483648L
		|| value > 2147483647L)
		return (false);
	*out = (int)value;
	return (true);
}
