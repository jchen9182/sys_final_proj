# File Explorer

## Required libraries
- GTK+ (for GUI work)
  - ```sudo apt install gtk+3.0```

## Proposal
**Members**
  - Justin Chen (period 4)
  - Samuel Fang (period 4)
  - Kevin Li (period 5)

This project is a GUI-based file explorer. Examples would include File Explorer on Windows, Finder on macOS, and Nautilus on Ubuntu.

**UI**
  - It can be used via a pointing device like a mouse or trackpad, with keyboard shortcuts as well (e.g. the Delete key would delete a file).
  - It will be a lot more user friendly due to not having to memorize commands like ls, rm, mkdir, etc.
  - Primary mouse click to select/highlight a file
  - Double click to execute a file with the appropriate program for the file extension (further explained in the technical design section)
  - Secondary mouse click to bring up additional actions (such as to delete, rename, or view the properties of a file)
  - Click and drag to select multiple files at once

**Technical Design**
  - Systems concepts used:
    - Allocating memory
    - Working with files
    - Processes (fork, exec, etc.)
    - Finding information about files (stat and such)

  - Show the current working directory in a box at the top or bottom of the window at all times: getcwd(), 200 size char array should be enough for 99% of cases
  - Showing files in a directory [ALLOCATING MEMORY + WORKING WITH FILES]
    - Use opendir() and readdir() functions and read individual files/folders into a malloc-d 2D array (5000 long for now, can be any size we want really)
    - readdir() reads each directory entry one by one, don't even need to parse anything
    - For now, show files row by row; if we have time, we can add a "view" feature that can arrange the icons in other ways (currently don't know anything about GTK+ so will have to come back to update this later)

 - [WORKING WITH FILES]
   - Run a file [FORK AND EXEC]
     - strsep(filename, ".") to obtain file extension (for now, just don't do anything if there is no file extension)
     - Use switch statement in c, use the appropriate program for the file extension
     - If a file extension is not recognized/coded into our program, it will be the default case, which is to not do anything.
       - e.g. for .txt and other raw text files: execute gedit with the text file (don't know how to obtain the default program yet, and we know that gedit is present on every single Ubuntu machine)
       - e.g. for .jpg, .png, other image files: execute eog with the image file

   - Create a file: open("Untitled Document", O_CREAT, 0666) (0666 is default for Linux)
   - Create a directory: mkdir(char *dirname)
   - Rename a file: rename(char *oldname, char *newname)
   - Delete a file: remove(char *filename)
   - View properties of a file: stat(char *filename, char* buffer) [FINDING INFO ABOUT FILES]
     - Don't even need to click the properties button, just clicking on a file should show basic info like file size on the bottom.

**Timeline**
  - **[2019-12-28]** Get a "Hello, World!" window showing with GTK+
    - Worker(s) on this task: Justin Chen

  - **[2019-12-31]** Generate an array of files via piping
    - Worker(s) on this task: Kevin Li

  - **[2019-01-03]** Parse individual files for their file extension
    - Worker(s) on this task: Samuel Fang

  - **[2020-01-06]** Execute files accordingly using their file extension
    - Worker(s) on this task: Kevin Li

  - **[2019-01-09]** Get all the properties of a file
    - Worker(s) on this task: Samuel Fang

  - **[2019-01-12]** File operations: create file, create directory, rename file, delete file, etc.
    - Worker(s) on this task: Samuel Fang, Kevin Li

  - **[2019-01-15]** {LAST BIG TASK}: convert all of the above into GUI form with GTK+
    - Worker(s) on this task: Justin Chen (main), with assistance from Samuel & Kevin

  - [2019-01-16] Last work day; hand in project by tomorrow morning
