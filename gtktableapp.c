#include <stdlib.h>
#include <gtk/gtk.h>

int main (int argc, char *args[])
{
    /* Declare the Gtkwidget window to show main window*/
    GtkWidget *window, *table, *button, *entry;

    /*This below statement initializes all stuff needed to GTK and can parse
    command line arguments for the GTK application. */
    gtk_init(&argc, &args);

    /* Gtk Window initialization done here. New window created at the toplevel.
    */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    /* This function below set windows position at the center when it starts and
    second function set the title. */
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_title (GTK_WINDOW(window), "TABLEAPP");

    /* Initialization of table, with 3 columns, 3 rows and with TRUE homogenous
    property */
    table = gtk_table_new (3, 3, TRUE);
    button = gtk_button_new_with_label("Button");  // Button with label
    entry = gtk_entry_new();               // initialization of text entry

    /* These functions below attaches widgets to table with value according
    left, right, top and bottom values. */
    gtk_table_attach_defaults (GTK_TABLE(table), entry, 0, 3, 0, 1);
    gtk_table_attach_defaults (GTK_TABLE(table), button, 2, 3, 2, 3);

    /* This is function sends the exit signal to the program when Close [X]
    button is pressed. */
    g_signal_connect_swapped(G_OBJECT(window), "destroy",
                                G_CALLBACK(gtk_main_quit), NULL);

    /* Add a widget to GTK container, which is in this case is window */
    gtk_container_add(GTK_CONTAINER(window), table);
    /* Function to show the widget. */
    gtk_widget_show_all(window);

    /* This below function runs GTK main loop until the gtk_main_quit() is
    called. */
    gtk_main();
    return 0;
}
