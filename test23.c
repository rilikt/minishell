// #include <stdio.h>
// #include <sys/stat.h>

// int	main(int argc, char *argv[])
// {
// 	if (argc != 2)
// 	{
// 		printf("Usage: %s <path>\n", argv[0]);
// 		return (1);
// 	}

// 	const char *path = argv[1];
// 	struct stat path_stat;

// 	// Call stat() to retrieve information about the file
// 	if (stat(path, &path_stat) != 0)
// 	{
// 		perror("stat");
// 		return (1);
// 	}

// 	// Check if the path is a directory
// 	if (S_ISDIR(path_stat.st_mode))
// 	{
// 		printf("%s is a directory.\n", path);
// 	}
// 	// Check if the path is a regular file
// 	else if (S_ISREG(path_stat.st_mode))
// 	{
// 		printf("%s is a regular file.\n", path);
// 	}
// 	// Handle other file types (e.g., symbolic link, socket, etc.)
// 	else
// 	{
// 		printf("%s is of another file type.\n", path);
// 	}

// 	return (0);
// }