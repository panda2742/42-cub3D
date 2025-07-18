
#include "../../include/mandatory/parse_cub_file.h"

int get_file_size(char *config_file)
{
  int fd;
  char *line;
  int i;

  fd = open(config_file, O_RDONLY);
  if (fd < 0)
  {
    //a virer 
    perror("open");
    return (OPEN_ERROR);
  }
  line = get_next_line(fd);
  if (!line)
  {
    close(fd);
    return (0);
  }
  i = 1;
  while (line)
  {
    free(line);
    line = get_next_line(fd);
    if (!line)
      break ;
    i++;
  }
  close(fd);
  return (i);
}

int get_file_content(char ***file_content, int fd, int size)
{
  char *line;
  int i;

  i = 0;
  *file_content = malloc(sizeof(char *) * (size + 1));
  if (!*file_content)
    return (MALLOC_ERROR);
  line = get_next_line(fd);
  if (!line && i != size)
    return (MALLOC_ERROR);
  while (line)
  {
    (*file_content)[i] = ft_strdup(line);
    if (!(*file_content)[i])
    {
      while (--i >= 0)
        free((*file_content)[i]);
      free(*file_content);
    }
    free(line);
    line = get_next_line(fd);
    i++;
    if (!line && i != size)
    {
      while (i >= 0) 
      {
        free(file_content[i]);
        i--;
      }
      free(*file_content);
      return (MALLOC_ERROR);
    }
  }
  (*file_content)[i] = NULL;
  return (0);
}

int is_valid_map_path(char *map, char ***file_content)
{
  int size;
  int fd;
  int exit_code;

  size = get_file_size(map);
  if (size == 0)
    return (FILE_EMPTY);
  if (size < 0)
    return (size);
  fd = open(map, O_RDONLY);
  if (fd < 0)
    return (OPEN_ERROR);
  exit_code = get_file_content(file_content, fd, size);
  close(fd);
  return (exit_code);
}
