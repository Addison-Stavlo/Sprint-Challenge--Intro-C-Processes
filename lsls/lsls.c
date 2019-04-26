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
  if (argc <= 1)
  {
    dirName = ".";
  }
  else
  {
    dirName = argv[1];
  }
  // Open directory
  DIR *dir;
  if ((dir = opendir(dirName)) == NULL)
  {
    perror("cannot open file");
    exit(1);
  }

  // keep track of how many times we read from the directory
  int timesRead = 0;
  struct dirent *entry;
  // Repeatly read and print entries
  while ((entry = readdir(dir)) != NULL)
  {
    timesRead += 1;
    // struct to store size info
    struct stat buf;
    // create string of full path to get size info
    char *fullPath = malloc(strlen(dirName) + strlen(entry->d_name) + 1);
    strcat(fullPath, dirName);
    strcat(fullPath, "/");
    strcat(fullPath, entry->d_name);
    // get info from path, store in buf
    if (stat(fullPath, &buf) == -1)
    {
      // some error, move onto next read
      continue;
    }

    if (buf.st_size == 512) // assume directory
    {
      // print out directory name
      printf("<DIR>  %s\n", entry->d_name);

      //proceed to print out directory contents

      //close original dir for now
      closedir(dir);

      // re-init directory variables and open
      struct dirent *subEntry;
      DIR *subDir;
      if ((subDir = opendir(fullPath)) == NULL)
      {
        perror("cannot open sub-directory");
        continue;
      }

      // read through the sub directory and print stuff
      while ((subEntry = readdir(subDir)) != NULL)
      {
        // create string for path to get info
        char *subPath = malloc(strlen(fullPath) + strlen(subEntry->d_name) + 1);
        strcat(subPath, fullPath);
        strcat(subPath, "/");
        strcat(subPath, subEntry->d_name);
        // get info, store in buf again
        if (stat(subPath, &buf) == -1)
        {
          // some error, move onto next read
          continue;
        }

        if (buf.st_size == 512)
        {
          // print directory name
          printf("          <DIR>   %s\n", subEntry->d_name);
        }
        else
        {
          // print file name and size
          printf("          %zu   %s\n", buf.st_size, subEntry->d_name);
        }
      }
      closedir(subDir);

      // re-open original directory and catch up on how many times we have read it
      dir = opendir(dirName);
      int i = 0;
      while (i < timesRead)
      {
        subEntry = readdir(dir);
        i++;
      }
    }
    else
    {
      // print file from original path
      printf("%zu  %s\n", buf.st_size, entry->d_name);
    }
  }
  // Close directory
  closedir(dir);

  return 0;
}