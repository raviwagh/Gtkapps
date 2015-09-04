#include <stdlib.h>
#include <gtk/gtk.h>
/* Created structure of GtkWidgets or custom widget at global scope so any
function in the program can access the widgets */
typedef struct {
    GtkWidget *value1, *value2, *value3, *value4;
} entrygrouped;

/* Entry value getter guint variables, the guint variable are the int form of
GTK */
guint ival1, ival2, ival3, ival4;

/* When clicked events generated in the gtk_main event the statement
g_signal_connect calls the callback with arguments specified. */
void button_clicked (entrygrouped *widget)
{
    const gchar *cvalue1, *cvalue2, *cvalue3, *cvalue4;
    cvalue1 = gtk_entry_get_text (GTK_ENTRY(widget->value1));
    cvalue2 = gtk_entry_get_text (GTK_ENTRY(widget->value2));
    cvalue3 = gtk_entry_get_text (GTK_ENTRY(widget->value3));
    cvalue4 = gtk_entry_get_text (GTK_ENTRY(widget->value4));

    ival1 = (guint)atoi(cvalue1);
    ival2 = (guint)atoi(cvalue2);
    ival3 = (guint)atoi(cvalue3);
    ival4 = (guint)atoi(cvalue4);

    g_print("ENTRY VALUES = %s %s %s %s\n", cvalue1, cvalue2, cvalue3, cvalue4);
    g_print("ENTRY NUMS = %d %d %d %d\n", ival1, ival2, ival3, ival4);
}
int main (int argc, char *args[])
{
    /* Declare the Gtkwidget window to show main window*/
    GtkWidget *window, *uptable, *downtable, *button, *button2, *vbox;

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

    /* These following statement create a pointer of structure instance, the
    memory allocation of structure instance to the structure pointer is needed.
    Which is done by the following statement. */
    entrygrouped *eg;
    eg = g_slice_new(entrygrouped);

    /* Initialization of tables */
    uptable = gtk_table_new (3, 3, FALSE);
    downtable = gtk_table_new (3, 3, FALSE);
    button = gtk_button_new_with_label("Submit");   // Button with label
    button2 = gtk_button_new_with_label("Button");  // Button with label
    vbox = gtk_vbox_new(FALSE, 2);                  // GTK vbox

    /* initialization of text entries */
    eg->value1 = gtk_entry_new();
    eg->value2 = gtk_entry_new();
    eg->value3 = gtk_entry_new();
    eg->value4 = gtk_entry_new();

    /* These functions below attaches widgets to table with value according
    left, right, top and bottom values. */
    gtk_table_attach_defaults (GTK_TABLE(uptable), eg->value1, 0, 1, 0, 1);
    gtk_table_attach_defaults (GTK_TABLE(uptable), eg->value2, 1, 2, 0, 1);
    gtk_table_attach_defaults (GTK_TABLE(uptable), eg->value3, 0, 1, 1, 2);
    gtk_table_attach_defaults (GTK_TABLE(uptable), eg->value4, 1, 2, 1, 2);
    gtk_table_attach_defaults (GTK_TABLE(uptable), button, 1, 2, 2, 3);

    /* This below function packs both table into a vertical box alignment, this
    method is used because GTK window can have only one container which is added
    later in this program. The packing is done from start. */
    gtk_box_pack_start (GTK_BOX(vbox), uptable, 0, 0, 0);
    gtk_box_pack_start (GTK_BOX(vbox), downtable, 0, 0, 0);

    /* The program flow go to the callback function when click event happens
    on specified button widget. */
    g_signal_connect(G_OBJECT(button), "clicked",
                            G_CALLBACK(button_clicked), eg);

    /* This is callback function which sends the exit signal to the program when
    Close [X] button is pressed. */
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
