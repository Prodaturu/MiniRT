#include "./include/minirt.h"

static void	print_error(const char *message)
{
	fprintf(stderr, "Error\n%s\n", message);
}

int	file_checker(int argc, char **argv, t_main_rt *rt, char *err, size_t size)
{
	const char	*ext;

	if (argc != 2 && argc != 3)
		return (set_error(err, size, "usage: ./miniRT <scene.rt> [--save]"), 0);
	ext = strrchr(argv[1], '.');
	if (ext == NULL || strcmp(ext, ".rt") != 0)
		return (set_error(err, size, "scene file must use the .rt extension"), 0);
	if (argc == 3 && strcmp(argv[2], "--save") != 0)
		return (set_error(err, size, "optional second argument must be --save"), 0);
	rt->save_mode = (argc == 3);
	snprintf(rt->scene_path, sizeof(rt->scene_path), "%s", argv[1]);
	return (1);
}

int	main(int argc, char **argv)
{
	t_main_rt	rt;
	char		err[256];

	memset(&rt, 0, sizeof(rt));
	memset(err, 0, sizeof(err));
	if (!file_checker(argc, argv, &rt, err, sizeof(err))
		|| !parse_scene_file(argv[1], &rt.scene, err, sizeof(err))
		|| !init_scene_struct(&rt.scene, err, sizeof(err)))
	{
		scene_free(&rt.scene);
		print_error(err[0] ? err : "unknown failure");
		return (1);
	}
	if (rt.save_mode)
	{
		scene_render(&rt);
		if (!write_bmp(&rt, err, sizeof(err)))
		{
			free(rt.framebuffer);
			scene_free(&rt.scene);
			print_error(err[0] ? err : "failed to save bitmap");
			return (1);
		}
	}
	else if (!renderer(&rt, err, sizeof(err)))
	{
		free(rt.framebuffer);
		scene_free(&rt.scene);
		print_error(err[0] ? err : "unknown failure");
		return (1);
	}
	free(rt.framebuffer);
	scene_free(&rt.scene);
	return (0);
}
