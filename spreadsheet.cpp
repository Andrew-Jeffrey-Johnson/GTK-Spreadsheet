/*
	Author: Andrew Johnson
	Created: 26 August 2016
	Edited: 8 October 2023
	Description: Creates a 10x11 grid of entries. Entering floating-point 
				 values updates that column's bottom-row entry to be the
				 sum of the column. Text is treated as 0 for the sum.
				 The save button overwrites the file "output.csv" in the
				 same subdirectory as the executable. It saves the
				 contents of all entries in the grid.
	Compile via make file:
		make
	Compile via g++:
		g++ -std=c++11 spreadsheet.cpp -o spreadsheet $(pkg-config gtkmm-3.0 --cflags --libs)
	GTK 3 and gtkmm required
		
*/

#include <gtkmm.h>
#include <fstream>
#include <vector>
#include <iostream>


// Number of rows and columns of entries
#define WIDTH 10
#define HEIGHT 10


/*
	Entire window object. Holds all entries, the totals label, and the save button
*/
class SpreadsheetWindow : public Gtk::Window 
{
	public:
		SpreadsheetWindow();
		virtual ~SpreadsheetWindow(); // virtual prevents memory leak

	private:
		// Signal handler
		void on_button_clicked();

		// Widgets
		Gtk::Grid organizing_grid;
		Gtk::Button save_button;
		std::vector<Gtk::Entry*> spreadsheet_cells;
};


/*
	Constructor for SpreadsheetWindow fills itself with entries,
	the totals label, and the save button
*/
SpreadsheetWindow::SpreadsheetWindow() 
{
    set_border_width(11);
    save_button.set_label("Save to output.csv");
    save_button.signal_clicked().connect(sigc::mem_fun(*this, &SpreadsheetWindow::on_button_clicked));
    
    // Create all cells and add them to spreadsheet_cells
    for (int i = 0; i < WIDTH; i++) 
    {
        for (int j = 0; j < HEIGHT; j++) 
        {
            Gtk::Entry* entry = Gtk::manage(new Gtk::Entry());
			if (j >= HEIGHT-1) {
				entry->set_editable(false);
			}
            organizing_grid.attach(*entry, i+1, j+1, 1, 1);
            spreadsheet_cells.push_back(entry);
        }
    }

    // Connect signal_changed() function
    for (int i = 0; i < WIDTH; i++) 
    {
        for (int j = 0; j < HEIGHT - 1; j++) 
        {
            Gtk::Entry* entry = spreadsheet_cells[j + i*HEIGHT];
            entry->signal_changed().connect([this, entry, i] ()
			{
				double sum = 0.0;

				for (int k = 0; k < HEIGHT-1; k++) 
				{
					Gtk::Entry* column_entry = spreadsheet_cells[k + i*HEIGHT];
					try 
					{
						sum += std::stod(column_entry->get_text());
					} 
					catch (const std::invalid_argument& e) 
					{
						// Ignore cells with non-numeric text
					}
				}

				spreadsheet_cells[i*HEIGHT + HEIGHT-1]->set_text(std::to_string(sum));
			});
        }
    }
    
	Gtk::Label* totals_label = Gtk::manage(new Gtk::Label("Totals"));
    organizing_grid.attach(*totals_label, 0, HEIGHT, 1, 1);
	
    organizing_grid.attach(save_button, 1, HEIGHT+1, WIDTH, 1);
    add(organizing_grid);
    show_all_children();
}

/*
	Obligatory destructor
*/
SpreadsheetWindow::~SpreadsheetWindow() {}


/*
	Formats and exports the spreadsheet as a CSV file after
	clicking the save button
*/
void SpreadsheetWindow::on_button_clicked() 
{
    std::ofstream file("output.csv");
    
    for (size_t i = 0; i < spreadsheet_cells.size(); i++) 
	{
		size_t column = i%WIDTH;
		size_t row = i/WIDTH;
        file << spreadsheet_cells[column*HEIGHT + row]->get_text();
        
        if (i % WIDTH != WIDTH-1) 
		{
            file << ",";
        } 
		else 
		{
            file << "\n";
        }
    }
}


/*
	Create app, create window, and run app on window.
*/
int main(int argc, char **argv) 
{
	// Smart pointer that refers to an instance of Gtk::Application
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv);
    SpreadsheetWindow entire_window;
    return app->run(entire_window);// Shows window and exits when closed
}
