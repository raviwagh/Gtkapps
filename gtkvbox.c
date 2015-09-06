#include <stdlib.h>
#include <gtk/gtk.h>

int main (int argc, char *args[])
{
    /* Declare the Gtkwidget window to show main window*/
    GtkWidget *window, *vbox, *button1, *button2, *button3, *button4;

    /*This below statement initializes all stuff needed to GTK and can parse
    command line arguments for the GTK application. */
    gtk_init(&argc, &args);

    /* Gtk Window initialization done here. New window created at the toplevel.
    Below statements set position and title of the window. */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position (GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_title (GTK_WINDOW(window), "VBOX");

    /* The vertical box initialization done below, other widget are packed in
    this box. */
    vbox = gtk_vbox_new(FALSE, 5);
    /* Some button widgets with labels, to create buttons. */
    button1 = gtk_button_new_with_label("BUTTON 1 With Start Packing");
    button2 = gtk_button_new_with_label("BUTTON 2 With Start Packing");
    button3 = gtk_button_new_with_label("BUTTON 3 With End Packing");
    button4 = gtk_button_new_with_label("BUTTON 4 With End Packing");

    /* The button packing done below, the first two buttons packed with start,
    where other two buttons packed with end. */
    gtk_box_pack_start (GTK_BOX(vbox), button1, 0, 0, 0);
    gtk_box_pack_start (GTK_BOX(vbox), button2, 0, 0, 0);
    gtk_box_pack_end (GTK_BOX(vbox), button3, 0, 0, 0);
    gtk_box_pack_end (GTK_BOX(vbox), button4, 0, 0, 0);

    /* Add a widget to GTK container. */
    gtk_container_add(GTK_CONTAINER(window), vbox);

    /* This function allows to show all content in a widget. */
    gtk_widget_show_all(window);

    /* The program flow go to the callback function when click event happens
    on specified button widget. */
    g_signal_connect_swapped(G_OBJECT(window), "destroy",
                                        G_CALLBACK(gtk_main_quit), NULL);

    /* This below function runs GTK main loop until the gtk_main_quit() is
    called. */
    gtk_main();
    return 0;
}
