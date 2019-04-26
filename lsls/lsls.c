#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
/**
 * Main
 */
int main(int argc, char **argv)
{
  char *dirName;
  // Parse command line
  printf("%d\n", argc);
  if (argc <= 1)
  {
    dirName = ".";
  }
  else
  {
    dirName = argv[1];
  }
  printf("%s\n", dirName);
  // Open directory
  DIR *dir = opendir(dirName);
  if ((dir = opendir(dirName)) == NULL)
  {
    perror("cannot open file");
    exit(1);
  }

  struct dirent *entry;
  // Repeatly read and print entries
  while ((entry = readdir(dir)) != NULL)
  {
    // struct stat buf;
    char *fullPath = malloc(strlen(dirName) + strlen(entry->d_name) + 1);
    strcat(fullPath, "/");
    strcat(fullPath, dirName);
    strcat(fullPath, entry->d_name);
    printf("%s\n", fullPath);

    // strcat(fullPath, entry->d_name);
    // strcat(fullPath, dirName);
    // strcat(fullPath, entry->d_name);
    // printf("%s\n", fullPath);
    // int fileSize = stat()
    printf("%s\n", entry->d_name);
  }
  // Close directory
  closedir(dir);

  return 0;
}