#include <stdlib.h>
#include <gtk/gtk.h>
gboolean buttonbool = FALSE;

typedef struct {
    GtkWidget *value1, *value2, *value3, *value4;
} entrygrouped;

static GtkWidget *button2 = 0;

gfloat fval1, fval2, fval3, fval4;

void button_clicked (gpointer data, entrygrouped *widget)
{
    const gchar *cvalue1, *cvalue2, *cvalue3, *cvalue4;
    cvalue1 = gtk_entry_get_text (GTK_ENTRY(widget->value1));
    cvalue2 = gtk_entry_get_text (GTK_ENTRY(widget->value2));
    cvalue3 = gtk_entry_get_text (GTK_ENTRY(widget->value3));
    cvalue4 = gtk_entry_get_text (GTK_ENTRY(widget->value4));

    fval1 = (gfloat)atof(cvalue1);
    fval2 = (gfloat)atof(cvalue2);
    fval3 = (gfloat)atof(cvalue3);
    fval4 = (gfloat)atof(cvalue4);

    g_print("ENTRY VALUES = %s %s %s %s\n", cvalue1, cvalue2, cvalue3, cvalue4);
    g_print("ENTRY NUMS = %f %f %f %f\n", fval1, fval2, fval3, fval4);
}

void showid(gpointer data, GtkWidget *widget)
{
    if (buttonbool == TRUE)
    {
        gtk_alignment_set(GTK_ALIGNMENT(widget), fval1, fval2, fval3, fval4);
        gtk_container_remove(GTK_CONTAINER(widget), button2);
        g_object_ref(button2);
        button2 = gtk_button_new_with_label("BUTTON");
        gtk_container_add (GTK_CONTAINER(widget), button2);
    } else {
        gtk_alignment_set(GTK_ALIGNMENT(widget), fval1, fval2, fval3, fval4);
        gtk_container_add (GTK_CONTAINER(widget), button2);
        buttonbool = TRUE;
    }
    gtk_widget_show(button2);
}
void file_new (GtkWidget *widget, GtkWidget *win)
{
    GtkWidget *dialog;
    dialog = gtk_file_chooser_dialog_new ("Open File",
				      GTK_WINDOW(win),
				      GTK_FILE_CHOOSER_ACTION_OPEN,
				      GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
				      GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
				      NULL);
    if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)
    {
        char *filename;
        filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
        g_print("File name = %s\n", filename);
        //open_file (filename);
        //g_free (filename);
    }

    gtk_widget_destroy (dialog);

}
int main (int argc, char *args[])
{
    GtkWidget *window, *uptable, *align, *button, *vbox, *instr;
    GtkWidget *menu, *open, *file_menu, *menu_bar, *exit;
    gtk_init(&argc, &args);

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_title (GTK_WINDOW(window), "MENUAPP");

    entrygrouped *eg;
    eg = g_slice_new(entrygrouped);

    instr = gtk_label_new (" Enter the float values to align the widget ");
    uptable = gtk_table_new (2, 4, FALSE);
    align = gtk_alignment_new(0, 0, 0, 0);
    button = gtk_button_new_with_label("Submit");   // Button with label
    button2 = gtk_button_new_with_label("BUTTON");  // Button with label
    vbox = gtk_vbox_new(FALSE, 2);                  // GTK vbox

    menu = gtk_menu_new();
    open = gtk_image_menu_item_new_from_stock(GTK_STOCK_NEW, NULL);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), open);
    gtk_widget_show(open);

	exit = gtk_image_menu_item_new_from_stock (GTK_STOCK_QUIT, NULL);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), exit);
    gtk_widget_show(exit);

    file_menu = gtk_menu_item_new_with_label ("File");
    gtk_menu_item_set_submenu (GTK_MENU_ITEM(file_menu), menu);

    gtk_widget_show(open);
    gtk_widget_show(file_menu);

	menu_bar = gtk_menu_bar_new();
	gtk_menu_shell_append (GTK_MENU_SHELL(menu_bar), file_menu);

    eg->value1 = gtk_entry_new();
    eg->value2 = gtk_entry_new();
    eg->value3 = gtk_entry_new();
    eg->value4 = gtk_entry_new();

    gtk_table_attach_defaults (GTK_TABLE(uptable), instr, 0, 3, 0, 1);
    gtk_table_attach_defaults (GTK_TABLE(uptable), eg->value1, 0, 1, 1, 2);
    gtk_table_attach_defaults (GTK_TABLE(uptable), eg->value2, 1, 2, 1, 2);
    gtk_table_attach_defaults (GTK_TABLE(uptable), eg->value3, 0, 1, 2, 3);
    gtk_table_attach_defaults (GTK_TABLE(uptable), eg->value4, 1, 2, 2, 3);
    gtk_table_attach_defaults (GTK_TABLE(uptable), button, 1, 2, 3, 4);

    gtk_widget_set_size_request(align, 300, 200);

    /* The second arguments gtk_box_pack_start(); is about expand properties of
    widget which was set 0 and third is about allocation fill properties is also
    set 0 in my previous program. */
    //gtk_box_set_homogeneous (GTK_BOX(vbox), TRUE);
    gtk_box_pack_start (GTK_BOX(vbox), menu_bar, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX(vbox), uptable, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX(vbox), align, TRUE, TRUE, 0);

    g_signal_connect(G_OBJECT(button), "clicked",
                            G_CALLBACK(button_clicked), eg);

    g_signal_connect(G_OBJECT(button), "clicked",
                            G_CALLBACK(showid), align);

    g_signal_connect_swapped(G_OBJECT(window), "destroy",
                                G_CALLBACK(gtk_main_quit), NULL);

    g_signal_connect(G_OBJECT(exit), "activate",
                                G_CALLBACK(gtk_main_quit), NULL);

    g_signal_connect(G_OBJECT(open), "activate",
                                G_CALLBACK(file_new), window);

	gtk_container_add(GTK_CONTAINER(window), vbox);

    gtk_widget_show_all(window);

    gtk_main();
    return 0;
}
