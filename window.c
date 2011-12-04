#include <gtk/gtk.h>

void 
on_window_destroy ( gpointer user_data)
{
        gtk_main_quit();
}

int
main (int argc, char *argv[])
{
        GtkBuilder              *builder;
        GtkWidget               *window;
        GtkWidget                *entry33;
        char *data = "11223344";
        
        gtk_init (&argc, &argv);
        
        builder = gtk_builder_new ();
        gtk_builder_add_from_file (builder, "window.xml", NULL);

        window = GTK_WIDGET (gtk_builder_get_object (builder, "window1"));
        entry33 = GTK_WIDGET( gtk_builder_get_object(builder, "entry33"));
        
        gtk_builder_connect_signals (builder, NULL);          
        g_object_unref (G_OBJECT (builder));
        
        
        gtk_entry_set_text(GTK_ENTRY(entry33),data);
        gtk_widget_show (window);       
        gtk_main ();
       
        
        return 0;
}
