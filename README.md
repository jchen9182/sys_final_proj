# File Explorer

**Members**
- Justin Chen (period 4)
- Samuel Fang (period 4)
- Kevin Li (period 5)

**Description**

This project is a GUI-based file explorer. Examples would include File Explorer on Windows, Finder on macOS, and Nautilus on Ubuntu.

**Required libraries**
- GTK+ (for GUI work)
  - ```sudo apt install libgtk-3-dev```
  - ```sudo apt install pkg-config``` (not technically "necessary", but the way GTK programs are compiled, it is best to have this installed. You are required to have this installed to use the makefile provided in this directory.)

**Instructions for running this project**

Type into a terminal session with the current directory being this repo:
```bash
make
make run
```

**How to use this program**
- Whatever is done from within this program should be reflected in a separate Nautilus window in the same directory (this repo).
- View current directory on the top
- Click a file with the right mouse button, which will bring up these options:
  - Open
    - Opens the selected file according to its file extension. i.e. .png with eog and .txt with gedit.
  - Delete (self explanatory, but gets entirely deleted rather than moving to the Trash)
  - Rename (will not allow you to rename to a file/folder that already exists)
  - Properties, where you may view:
    - The name of the file (can rename it from inside this window as well)
    - Size (both in bytes and converted to units like KB, MB, GB when appropriate)
    - Parent folder (this repo, since this program doesn't support changing folders)
    - Permissions in rwxrwxrwx form
    - The properties window is reduced for folders. For example, there is no point in displaying the size of a folder.
- Double click a file to open it as well
- The arrow in the top right of the window:
  - New File/Folder (same implementation)
    - Like rename, will not allow you to create a file/folder that already exists
  - About: shows description of project

**Known bugs**
- [POSSIBLE] Earlier in the project, there was a memory corruption bug that led to undefined behavior.
  - Was due to incorrect malloc-ing technique for the getfiles() function, which generates a 2D array of file names. Possibly fixed.
  - Because this is a GUI program, the program cannot be tested on the school computers easily to verify this conclusion. However, from the few times I've tested via x11, it appears to have been fixed.
  - If it hasn't, we implore Mr. DW to run the program a couple times until the undefined behavior stops.

**Abandoned features**
- Changing directories by entering/exiting folders
  - Would require a massive rewrite of the code, and I don't think I have the GTK knowledge to completely redraw the screen from outside the activate() function.
  - Not sure how to deal with the scope of GtkWidgets outside the function they were declared in (activate)
- The grid system is static. It will not adjust to you deleting files or creating  files and whatnot (never considered as a feature in the first place, but it is a basic feature of File Explorer, Finder, Nautilus, etc.)
- Keyboard shortcuts. We decided to try to implement this feature last but didn't realize there needed to be an install for GDK. It was too late to ask for it to be installed on the school computers.
- Clicking and dragging to select multiple files at once would have required much of our code to be rewritten. We don't have hte necessary code that tracks and moves the position of files.
