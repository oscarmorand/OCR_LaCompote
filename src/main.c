#include <gtk/gtk.h>

// SOLVER
#include "parser.h"
#include "solver.h"

// NEURAL NETWORK
#include "useNN.h"

// CONSTANTS
#define GRID_SIZE 9
#define FILE_NAME "test"


// Structure of the graphical user interface.
typedef struct UserInterface
{
    GtkWindow* window;              // Main window
    GtkFileChooserButton* fileLoad; // file chooser
    GtkButton* buttonChoose;        // choose image button
    GtkButton* buttonSolve;         // solver sudoku button
    GtkImage* image;                // choosed image

} UserInterface;


/*
    FUNCTIONS
*/


void on_fileLoad(GtkFileChooserButton *button, gpointer user_data)
{
    g_print("load this image\n");
}

void on_buttonChoose_clicked(GtkButton *button, gpointer user_data)
{
    g_print("choose this image\n");
}

void on_leftRotation_clicked(GtkButton *button, gpointer user_data)
{
    g_print("Left rotation\n");
}

void on_rightRotation_clicked(GtkButton *button, gpointer user_data)
{
    g_print("Right rotation\n");
}

void on_buttonSolve_clicked(GtkButton *button, gpointer user_data)
{
    char** grid = init_grid(GRID_SIZE);

    // fill grid with recognition of digits in the images
    fill_grid(GRID_SIZE, grid);

    g_print("Apres remplissage\n");
    print_grid(GRID_SIZE, grid);

    //Solving
    Solve(grid);

    g_print("Apres resolution\n");
    print_grid(GRID_SIZE, grid);

    //Saving
    Save(FILE_NAME, grid);

    //TODO
    // Enregistrer sous forme d'image

    free_grid(GRID_SIZE, grid);
}

int main(int argc, char *argv[])
{
    // Initializes GTK.
    gtk_init(NULL, NULL);

    // Constructs a GtkBuilder instance.
    GtkBuilder* builder = gtk_builder_new ();

    // Loads the UI description.
    // (Exits if an error occurs.)
    GError* error = NULL;
    if (gtk_builder_add_from_file(builder, "testglade.glade", &error) == 0)
    {
        g_printerr("Error loading file: %s\n", error->message);
        g_clear_error(&error);
        return 1;
    }

    // Gets the widgets.
    GtkWindow* window = GTK_WINDOW(gtk_builder_get_object(builder, "window"));
    GtkFileChooserButton* fileLoad = GTK_FILE_CHOOSER_BUTTON(gtk_builder_get_object(builder, "fileLoad"));
    GtkButton* leftRotation = GTK_BUTTON(gtk_builder_get_object(builder, "leftRotation"));
    GtkButton* rightRotation = GTK_BUTTON(gtk_builder_get_object(builder, "rightRotation"));
    GtkButton* buttonChoose = GTK_BUTTON(gtk_builder_get_object(builder, "buttonChoose"));
    GtkButton* buttonSolve = GTK_BUTTON(gtk_builder_get_object(builder, "buttonSolve"));

    // Creates the "Game" structure.
    UserInterface ui =
    {
        .window = window,
        .fileLoad = fileLoad,
        .buttonChoose = buttonChoose,      
        .buttonSolve = buttonSolve, 
        .image = NULL,
    };

    // Connects event handlers.
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(fileLoad, "file_set", G_CALLBACK(on_fileLoad), &ui);
    g_signal_connect(leftRotation, "clicked", G_CALLBACK(on_leftRotation_clicked), NULL);
    g_signal_connect(rightRotation, "clicked", G_CALLBACK(on_rightRotation_clicked), NULL);
    g_signal_connect(buttonChoose, "clicked", G_CALLBACK(on_buttonChoose_clicked), NULL);
    g_signal_connect(buttonSolve, "clicked", G_CALLBACK(on_buttonSolve_clicked), NULL);

    // Runs the main loop.
    gtk_main();

    // Exits.
    return 0;
}