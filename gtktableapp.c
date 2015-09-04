#include <stdlib.h>
#include <gtk/gtk.h>

int main (int argc, char *args[])
{
    /* Declare the Gtkwidget window to show main window*/
    GtkWidget *window, *uptable, *downtable, *button, *button2, *vbox;
    GtkWidget *value1, *value2, *value3, *value4;

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

    /* Initialization of tables */
    uptable = gtk_table_new (3, 3, FALSE);
    downtable = gtk_table_new (3, 3, FALSE);
    button = gtk_button_new_with_label("Submit");  // Button with label
    vbox = gtk_vbox_new(FALSE, 2);          // GTK vbox

    /* initialization of text entries */
    value1 = gtk_entry_new();
    value2 = gtk_entry_new();
    value3 = gtk_entry_new();
    value4 = gtk_entry_new();

    /* These functions below attaches widgets to table with value according
    left, right, top and bottom values. */
    gtk_table_attach_defaults (GTK_TABLE(uptable), value1, 0, 1, 0, 1);
    gtk_table_attach_defaults (GTK_TABLE(uptable), value2, 1, 2, 0, 1);
    gtk_table_attach_defaults (GTK_TABLE(uptable), value3, 0, 1, 1, 2);
    gtk_table_attach_defaults (GTK_TABLE(uptable), value4, 1, 2, 1, 2);
    gtk_table_attach_defaults (GTK_TABLE(uptable), button, 1, 2, 2, 3);

    /* This below function packs both table into a vertical box alignment, this
    method is used because GTK window can have only one container which is added
    later in this program. The packing is done from start. */
    gtk_box_pack_start (GTK_BOX(vbox), uptable, 0, 0, 0);
    gtk_box_pack_start (GTK_BOX(vbox), downtable, 0, 0, 0);

    /* This is function sends the exit signal to the program when Close [X]
    button is pressed. */
    g_signal_connect_swapped(G_OBJECT(window), "destroy",
                                G_CALLBACK(gtk_main_quit), NULL);

    /* Add a widget to GTK container, which is in this case is window */
    gtk_container_add(GTK_CONTAINER(window), vbox);

    /* Function to show the widget. */
    gtk_widget_show_all(window);

    /* This below function runs GTK main loop until the gtk_main_quit() is
    called. */
    gtk_main();
    return 0;
}
