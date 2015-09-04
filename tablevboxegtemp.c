#include <stdlib.h>
#include <gtk/gtk.h>

typedef struct _entrygrouped {
    GtkWidget *value1, *value2, *value3, *value4;
} entrygrouped;

guint ival1, ival2, ival3, ival4;

void button_clicked(gpointer data, entrygrouped *widget)
{
    const gchar *value1, *value2, *value3, *value4;

    value1 = gtk_entry_get_text (GTK_ENTRY(widget->value1));
    value2 = gtk_entry_get_text (GTK_ENTRY(widget->value2));
    value3 = gtk_entry_get_text (GTK_ENTRY(widget->value3));
    value4 = gtk_entry_get_text (GTK_ENTRY(widget->value4));

    ival1 = (guint)atoi(value1);
    ival2 = (guint)atoi(value2);
    ival3 = (guint)atoi(value3);
    ival4 = (guint)atoi(value4);

    g_print("ENTRY VALUES = %s %s %s %s\n", value1, value2, value3, value4);
    g_print("ENTRY NUMS = %d %d %d %d\n", ival1, ival2, ival3, ival4);

}

int main (int argc, char *args[])
{
    GtkWidget *window, *vbox, *uptable, *downtable, *label;
    GtkWidget  *button, *button2;
    gtk_init(&argc, &args);

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    entrygrouped *eg;
    eg = g_slice_new(entrygrouped);

    vbox = gtk_vbox_new(FALSE, 2);
    uptable = gtk_table_new (3, 4, FALSE);
    downtable = gtk_table_new (3, 3, TRUE);

    label = gtk_label_new (" Enter the values to position the widget ");
    eg->value1 = gtk_entry_new();
    eg->value2 = gtk_entry_new();
    eg->value3 = gtk_entry_new();
    eg->value4 = gtk_entry_new();
    button = gtk_button_new_with_label ("Submit");
    button2 = gtk_button_new_with_label("BUTTON");

    gtk_table_attach_defaults (GTK_TABLE(uptable), label, 0, 3, 0, 1);
    gtk_table_attach_defaults (GTK_TABLE(uptable), eg->value1, 0, 1, 1, 2);
    gtk_table_attach_defaults (GTK_TABLE(uptable), eg->value2, 1, 2, 1, 2);
    gtk_table_attach_defaults (GTK_TABLE(uptable), eg->value3, 0, 1, 2, 3);
    gtk_table_attach_defaults (GTK_TABLE(uptable), eg->value4, 1, 2, 2, 3);
    gtk_table_attach_defaults (GTK_TABLE(uptable), button, 1, 2, 3, 4);
    gtk_table_attach_defaults (GTK_TABLE(downtable), button2, ival1, ival2, ival3, ival4);

    gtk_box_pack_start(GTK_BOX(vbox), uptable, 0, 0, 0);
    gtk_box_pack_start(GTK_BOX(vbox), downtable, 0, 0, 0);

    g_signal_connect (G_OBJECT(button), "clicked",
                                G_CALLBACK(button_clicked), eg);

    gtk_widget_show_now(GTK_WIDGET(button2));

    g_signal_connect_swapped(G_OBJECT(window), "destroy",
                                G_CALLBACK(gtk_main_quit), NULL);

    gtk_container_add (GTK_CONTAINER(window), vbox);

    if (!gtk_widget_get_visible (window))
    gtk_widget_show_all (window);

    gtk_widget_show_all(window);

    gtk_main();
    return 0;
}
