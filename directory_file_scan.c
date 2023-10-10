            
/*======================================================================
| Searching directories for target files
|
| Name: directory_file_scan.c
|
| Written by: Alex Taveras-Crespo, February 2022
|
| Purpose: Accept a target directory from the command line to be processed (or accept blank input for current directory)
|          then use opendir(), readdir() and stat() to target files meeting largest/smallest (in bytes) and youngest and oldest (modified time)
|
| usage: ./directory_file_scan.c #target_directory
| e.g. ./directory_file_scan.c /home/COIS/3380/lab3
|
|
| Description of parameters:
| argv[1] - directory name to be processed and targeted
|
|
| Subroutines/libraries required:
| See include statements.
|
|-----------------------------------------------------------------------
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <limits.h>

//Max size macro of size 200
#define MAXSIZE 200


//See function definition for details
void fileDetails(char *path);


int main(int argc, char *argv[]) 
{
        //Data type representing directory stream
        DIR *dir;             
        //Data type representing the entry into specified directory
        struct dirent *dStruct;     
         //Data structure in which information containing file is contained
        struct stat fileStat;      

        //These 4 char pointer arrays will hold the names of the largest, smallest, oldest and youngest files
        char *largestName; 
        char *smallestName;
        char *oldestName;
        char *youngestName;

        //These two char arrays of max size 200 will hold the name of the directory, and the appended directory + file name
        char directoryName[MAXSIZE];
        char directoryPath[MAXSIZE];
        int dirLength;

        //These 4 char pointer arrays will hold the names of the largest, smallest, oldest and youngest directories concatenated with file name
        char largestPath[MAXSIZE];
        char smallestPath[MAXSIZE];
        char oldestPath[MAXSIZE];
        char youngestPath[MAXSIZE];
        
        //These data types are all used for iteration and comparison within the readdir() function
        int max = 0;
        int min = INT_MAX;
        time_t young = 0;
        time_t old = INT_MAX;


        //If the number of passed arguments exceeds two
        if (argc > 2)
        {
            printf("Too many arguments passed. Format expected: ./lab2 directory_name\n");
        }

        //If the number of passed arguments is one
        else if (argc == 1)
        {
            //Set the contents of the directory name to the current directory
            strcpy(directoryName, "./");
        }

        //If the number of passed arguments is two
        else if (argc == 2)
        {
           //Set argument length to length of passed argument, and set directory name to the contents of the passed argument
           dirLength = strlen(argv[1]);
           strncpy(directoryName, argv[1], dirLength);
           //Append a forward slash to the end of the directory name (for adding file names in the future)
           directoryName[dirLength] = '/';
        }

        //Open the directory stream using passed directory name
        dir = opendir(directoryName);
        
        //Only continue if the directory stream is not null
        if (dir != NULL)
        {
                //Set each of these char arrays to the name of the passed directory
                //I am setting these now to ensure that they are passed correctly, before the directoryName is accessed
                strcpy(largestPath, directoryName);
                strcpy(smallestPath, directoryName);
                strcpy(youngestPath, directoryName);
                strcpy(oldestPath, directoryName);

                //Continue to loop through the directory as long as the entry structure is not null
                while ((dStruct = readdir(dir)) != NULL)
                {
                        //Copy the contents of the directoryName into directoryPath
                        //Concatenate the entry structure filename member to the end of the full path
                        //I choose to strcpy into another string as this ensures I always overwrite the previous full directory path
                        strcpy(directoryPath, directoryName);
                        strcat(directoryPath, (dStruct->d_name));

                        //If the stat function call with full directory and stat structure is successful
                        if (stat(directoryPath, &fileStat) == 0)
                        {
                                //Filter only through regular files (no directories)
                                if (S_ISREG(fileStat.st_mode))
                                {

                                        //if the byte size of the stat structure (of current file) is larger than the max int
                                        if (fileStat.st_size > max)
                                        {
                                                //set max to the stat structure size, and set the largestName value to the current file
                                                max = (fileStat.st_size);
                                                largestName = (dStruct->d_name);
                                        }

                                        //if the byte size of the stat structure (of current file) is smaller than the max int
                                        if (fileStat.st_size < min)
                                        {
                                                //set min to the stat structure size, and set the smallestName value to the current file
                                                min = (fileStat.st_size);
                                                smallestName = (dStruct->d_name);
                                        }


                                        //if the modified time (in unix epoch time) is larger than the time_t variable young
                                        if (fileStat.st_mtime > young)
                                        {
                                                //set young to the stat structure modified time, and set youngestName to current file
                                                young = (fileStat.st_mtime);
                                                youngestName = (dStruct->d_name);
                                        }


                                        //If the modified time (in unix epoch time) is smaller than the time_t variable old
                                        if (fileStat.st_mtime < old)
                                        {
                                                //set old to the stat structure modified time, and set oldestName to current file
                                                old = (fileStat.st_mtime);
                                                oldestName = (dStruct->d_name);
                                        }
                                }

                        }

                }

                //This block of text concanenates the final largest, smallest, oldest and youngest file names to their respective paths.
                strcat(largestPath, largestName);
                strcat(smallestPath, smallestName);
                strcat(youngestPath, youngestName);
                strcat(oldestPath, oldestName);
                
                //The fileDetails function is called for each of the targeted path files
                fileDetails(largestPath);
                fileDetails(smallestPath);
                fileDetails(youngestPath);
                fileDetails(oldestPath);

                //Close the directory as we are no longer accessing the stream.
                closedir(dir);
        }

        //If the directory stream is null, continue here
        else
        {
                printf("Directory is null.");
        }


}

/*======================================================================
| Printing out the file details of a passed path
|
| Name: void fileDetails
|
| Written by: Alex Taveras-Crespo, February 2022
|
| Purpose: Accept a char array holding a path to a specific file. The function will print out the file in ls -l format, such that
|          file permissions, user ID, group ID, size in bytes, modified time and full path are displayed.
|
| usage: fileDetails(#pathToPass);
| e.g. fileDetails(lab2logfile.txt.cleaned);
|
|
| Description of parameters:
| char *path- path array to be processed and printed
|-----------------------------------------------------------------------
*/ 
void fileDetails(char *path)
{
        //stat structure file
        struct stat file;
        //Call stat on full path and stat struct
        if (stat(path, &file) == 0)
        {
            //Code taken from http://codewiki.wikidot.com/c:system-calls:stat for finding user permissions of a file
            printf((S_ISDIR(file.st_mode)) ? "d" : "-");
            printf((file.st_mode & S_IRUSR) ? "r" : "-");
            printf((file.st_mode & S_IWUSR) ? "w" : "-");
            printf((file.st_mode & S_IXUSR) ? "x" : "-");
            printf((file.st_mode & S_IRGRP) ? "r" : "-");
            printf((file.st_mode & S_IWGRP) ? "w" : "-");
            printf((file.st_mode & S_IXGRP) ? "x" : "-");
            printf((file.st_mode & S_IROTH) ? "r" : "-");
            printf((file.st_mode & S_IWOTH) ? "w" : "-");
            printf((file.st_mode & S_IXOTH) ? "x" : "-");

            //Print numerical id of user owner
            printf("\t%d", file.st_uid);
            //Print numerical id of group owner
            printf("\t%d", file.st_gid);

            //Print size in bytes
            printf("\t%d", file.st_size);

            //Print the modified date in local time
            char date[ 100 ] = "";
            //Method to return a string from a time object
            strftime(date, 100, "%Y-%m-%d %H:%M:%S", localtime(&file.st_mtime));
            printf("\t%s", date);

            //print the full path
            printf("\t%s\n", path);
        }
}
