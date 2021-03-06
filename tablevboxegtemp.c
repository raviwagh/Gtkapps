#include <stdlib.h>
#include <gtk/gtk.h>
gboolean buttonbool = FALSE;

/* Created structure of GtkWidgets or custom widget at global scope so any
function in the program can access the widgets */
typedef struct {
    GtkWidget *value1, *value2, *value3, *value4;
} entrygrouped;

GtkWidget *button2;
/* Entry value getter guint variables, the guint variable are the int form of
GTK */
guint ival1, ival2, ival3, ival4;

/* When clicked events generated in the gtk_main event the statement
g_signal_connect calls the callback with arguments specified. */
void button_clicked (gpointer data, entrygrouped *widget)
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
/* Function to attach new button to widget as per the values entered */
void showid(gpointer data, GtkWidget *widget)
{
    if (buttonbool == TRUE)
    {
        /* Here reference count of the widget is decreased by 1. */
        gtk_container_remove(GTK_CONTAINER(widget), GTK_WIDGET(button2));

        /* In below statement reference count of widget increased by 1 */
        g_object_ref(button2);
        button2 = gtk_button_new_with_label("SAME");

        gtk_table_attach_defaults (GTK_TABLE(widget), button2, ival1, ival2,
                                                            ival3, ival4);
    } else {
        gtk_table_attach_defaults (GTK_TABLE(widget), button2, ival1, ival2,
                                                            ival3, ival4);
        buttonbool = TRUE;
    }

    gtk_widget_show(button2);
}
/* This function prints the allocation of the widget */
void printalloc (GtkWidget *widget, GtkAllocation *alloc)
{
    g_print ("Height = %d, Width = %d\n", alloc->height, alloc->width);
    g_print ("X = %d, Y = %d\n", alloc->x, alloc->y);
}

int main (int argc, char *args[])
{
    /* Declare the Gtkwidget window to show main window*/
    GtkWidget *window, *uptable, *downtable, *button, *vbox, *instr;

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

    /* Initialization of label to instruct the purpose of the application */
    instr = gtk_label_new (" Enter the values to position the widget ");
    /* Initialization of tables */
    uptable = gtk_table_new (2, 4, FALSE);
    downtable = gtk_table_new (3, 3, TRUE);
    button = gtk_button_new_with_label("Submit");   // Button with label
    button2 = gtk_button_new_with_label("SAME");
                                                    // Button with label
    vbox = gtk_vbox_new(FALSE, 2);                  // GTK vbox

    /* initialization of text entries */
    eg->value1 = gtk_entry_new();
    eg->value2 = gtk_entry_new();
    eg->value3 = gtk_entry_new();
    eg->value4 = gtk_entry_new();

    /* These functions below attaches widgets to table with value according
    left, right, top and bottom values. */
    gtk_table_attach_defaults (GTK_TABLE(uptable), instr, 0, 3, 0, 1);
    gtk_table_attach_defaults (GTK_TABLE(uptable), eg->value1, 0, 1, 1, 2);
    gtk_table_attach_defaults (GTK_TABLE(uptable), eg->value2, 1, 2, 1, 2);
    gtk_table_attach_defaults (GTK_TABLE(uptable), eg->value3, 0, 1, 2, 3);
    gtk_table_attach_defaults (GTK_TABLE(uptable), eg->value4, 1, 2, 2, 3);
    gtk_table_attach_defaults (GTK_TABLE(uptable), button, 1, 2, 3, 4);

    gtk_widget_set_size_request(GTK_WIDGET(downtable), 300, 100);
    /* This below function packs both table into a vertical box alignment, this
    method is used because GTK window can have only one container which is added
    later in this program. The packing is done from start. Here the function
    arguments are as follows First argument is the Box widget to where the
    widgets are going to be packed, the second is widget which is going to be
    packed into the box, the third arguments is about expand properties to the
    child, fourth is about allocation properties towards the child, the last is
    gint the padding values regarding to child and its neighbors. */
    gtk_box_pack_start (GTK_BOX(vbox), uptable, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX(vbox), downtable, TRUE, TRUE, 0);

    /* The program flow go to the callback function when click event happens
    on specified button widget. */
    g_signal_connect(G_OBJECT(button), "clicked",
                            G_CALLBACK(button_clicked), eg);

    /*This function attaches the widget as per the values are entered. */
    g_signal_connect(G_OBJECT(button), "clicked",
                            G_CALLBACK(showid), downtable);
    /*Callback function with size-request signal to print the size of the widget
    */
    g_signal_connect(G_OBJECT(eg->value2), "size-request",
                                        G_CALLBACK(printalloc), NULL);

    /* This is callback function which sends the exit signal to the program when
    Close [X] button is pressed. */
    g_signal_connect_swapped(G_OBJECT(window), "destroy",
                                G_CALLBACK(gtk_main_quit), NULL);

    /* Add a widget to GTK container, which is in this case is window */
    gtk_container_add(GTK_CONTAINER(window), vbox);

    /* Function to show the widget. */
    gtk_widget_show_all(window);
    //gtk_widget_show(button2);

    /* This below function runs GTK main loop until the gtk_main_quit() is
    called. */
    gtk_main();
    return 0;
}
