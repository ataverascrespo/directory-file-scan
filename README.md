# directory-file-scan

This project was created for the Systems Programming course at Trent University. 

## Objective
The objective of this lab was to find 4 files in a target directory satisfying the conditions:
* largest file (in bytes)
* smallest file (in bytes)
* youngest file (by modification date)
* oldest file (by modification date)

To achieve this, the program accepts a target directory parameter from the command line. If no parameter is passed, it is assumed that the target directory is the one that the process is currently running from. **( ./ )**
Once a directory stream is established, the opendir(), readdir() and stat() system calls are used to target the largest/smallest files (in bytes) and the youngest and oldest files (modified time). 

The results of the file scans are then printed out in ls -l format. 

## Usage

Compile the C program
```
gcc directory_file_scan.c -o directory_file_scan
```

Scan a target directory!
```
./directory_file_scan /home/COIS/3380/lab3

-rw-rw-rw-	1001	1001	16436089	2017-07-30 11:44:47	/home/COIS/3380/lab3/lab3_dir.tar.gz
-rw-rw-rw-	1001	1001	379	2021-04-14 08:14:01	/home/COIS/3380/lab3/small_world.txt
-rw-rw-rw-	1001	1001	379	2021-04-14 08:14:01	/home/COIS/3380/lab3/small_world.txt
-rw-rw-rw-	1001	1001	1179	1980-01-01 00:01:28	/home/COIS/3380/lab3/C128.XTK
```
```
./directory_file_scan ~/3380/lab1

-rw-rw-r--	1143	1151	2994	2022-01-26 19:26:31	/home/ataverascrespo/3380/lab1/lab1_logfile.txt
-rw-rw-r--	1143	1151	190	2022-01-26 19:26:27	/home/ataverascrespo/3380/lab1/top_10_target_names.txt
-rw-rw-r--	1143	1151	2643	2022-01-26 19:27:58	/home/ataverascrespo/3380/lab1/ataverascrespo_lab1_logfile.cleaned
-rwxrw-r--	1143	1151	1427	2022-01-26 19:21:38	/home/ataverascrespo/3380/lab1/lab1_ipslog.sh
```
```
./directory_file_scan

-rwxrwxr-x	1143	1151	13144	2022-02-17 20:04:22	./directory_file_scan
-rw-rw-r--	1143	1151	0	2022-02-17 20:06:30	./lab2_logfile.txt
-rw-rw-r--	1143	1151	0	2022-02-17 20:06:30	./lab2_logfile.txt
-rw-rw-r--	1143	1151	10278	2022-02-17 20:04:21	./directory_file_scan.c
```

## What I Learned
* Command Line argument handling
* Low-level file operations
* File attribute extraction using stat() system calls
* Filesystem interaction using opendir() and readdir() system calls
* C Programming
