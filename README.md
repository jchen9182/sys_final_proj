# sys_final_proj
### Proposal:
    Project: Text Editor
    Members:
        - Justin Chen (period 4)
        - Samuel Fang (period 4)
        - Kevin Li (period 5)
    Description:
        - A GUI-based file explorer. Examples would include File Explorer on Windows, Finder on macOS, and Nautilus on Ubuntu.
    UI:
        - It can be used via a pointing device like a mouse or trackpad, with keyboard shortcuts as well (e.g. the Delete key would delete a file).
        - It will be a lot more user friendly due to not having to memorize commands like ls, rm, mkdir, etc. 
        - Primary mouse click to select/highlight a file
        - Double click to execute a file with the appropriate program for the file extension (further explained in the technical design section)
        - Secondary mouse click to bring up additional actions (such as to delete, rename, or view the properties of a file)
        - Click and drag to select multiple files at once
    Technical Design:
        - Show the current working directory in a box at the top or bottom of the window at all times: getcwd(), 200 size char array should be enough for 99% of cases
        - Showing files in a directory
            - Use a pipe to obtain what gets returned by running ls and feed it into a file stream: FILE * file = popen("ls", "r")
            - Read from the file stream and into a char array (should be rather big, maybe 10000 long?): fgets(array, sizeof(array), file)
            - Obtain every individual file: strsep(array, "\n")
            - For now, show files row by row; if we have time, we can add a "view" feature that can arrange the icons in other ways (currently don't know anything about GTK+ so will have to come back to update this later)
        - Working with files
            - Open a file
                - strsep(filename, ".") to obtain file extension (for now, just don't do anything if there is no file extension)
                - Use switch statement in c, use the appropriate program for the file extension
                    - If a file extension is not recognized/coded into our program, it will be the default case, which is to not do anything.
                    - e.g. for .txt and other raw text files: execute gedit with the text file (don't know how to obtain the default program yet, and we know that gedit is present on every single Ubuntu machine)
                    - e.g. for .jpg, .png, other image files: execute eog with the image file
                    - 
            - Create a file: open("Untitled Document", O_CREAT, 0666) (0666 is default for Linux)
            - Create a directory: mkdir(char *dirname)
            - Rename a file: rename(char *oldname, char *newname)
            - Delete a file: remove(char *filename)
    Timeline:
        -
