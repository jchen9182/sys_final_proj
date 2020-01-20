# File Explorer

**Members**
- Justin Chen (period 4)
- Samuel Fang (period 4)
- Kevin Li (period 5)

This project is a GUI-based file explorer. Examples would include File Explorer on Windows, Finder on macOS, and Nautilus on Ubuntu.

**Description**
- It can be used via a pointing device like a mouse or trackpad, with keyboard shortcuts as well (e.g. the Delete key would delete a file).
- It will be a lot more user friendly due to not having to memorize commands like ls, rm, mkdir, etc.
- Primary mouse click to select/highlight a file
- Double click to execute a file with the appropriate program for the file extension
- Secondary mouse click to bring up additional actions (such as to delete, rename, or view the properties of a file)
- Click and drag to select multiple files at once
- View current directory on the top

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
- Keyboard shortcuts? <-- what do you guys think
