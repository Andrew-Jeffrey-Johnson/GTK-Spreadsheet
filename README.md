# GTK-Spreadsheet
C++ GTK program creates a window with a 10X11 grid of entries that acts analogous to a spreadsheet.

Creates a 10x11 grid of entries. Entering floating-point values updates that column's bottom-row entry to be the sum of the column. Text is treated as 0 for the sum. 

The save button overwrites the file "output.csv" in the same subdirectory as the executable. It saves the contents of all entries in the grid.

Run <code>make</code> to compile via makefile.
  
To compile via <code>g++</code>, enter this into the command-line:

  <code>g++ -std=c++11 spreadsheet.cpp -o spreadsheet $(pkg-config gtkmm-3.0 --cflags --libs)</code>

GTK 3 or 4 and gtkmm 3 required for compilation

Example program usage:
![image](https://github.com/Andrew-Jeffrey-Johnson/GTK-Spreadsheet/assets/106950101/216e9d71-fbb9-4576-8a9c-0aa7c89499a1)

Example output:
![image](https://github.com/Andrew-Jeffrey-Johnson/GTK-Spreadsheet/assets/106950101/d8c946b4-9c42-4332-aa1f-0383918db895)
