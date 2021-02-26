#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "shm.h"

#include <gtk/gtk.h>
#include <gtkmm.h> 
#include "callback.h"

int main (int argc, char *argv[])
{
	
// 	Gtk::Main kit(argc, argv);

// 	// instantiate the widgets as defined by glade's XML file
// 	Glib::RefPtr<Gtk::Builder> builder =
// 		Gtk::Builder::create_from_file("HelloAgain.glade");

// 	// run with reference to the top level window
// 	Gtk::Window *pWin = NULL;
// 	builder->get_widget("window1", pWin);
// 	Gtk::Main::run(*pWin); 

	GtkBuilder              *builder;
	GtkWidget               *window;
        
	gtk_init (&argc, &argv);
        
	builder = gtk_builder_new ();
	gtk_builder_add_from_file (builder, "Controller.xml", NULL);

	window = GTK_WIDGET (gtk_builder_get_object (builder, "main_window"));
	gtk_builder_connect_signals (builder, NULL);
	g_object_unref (G_OBJECT (builder));
        
	gtk_widget_show (window);       
	gtk_main ();
        
	return 0;
}

// int main()
// {
// 	SharedMemory sm;

// 	sm.init(SHM_CLIENT);
// 	while(1){
// 	printf("%.2f, \t%.2f, \t%.2f\n",
// 		   sm.data->angle[0], sm.data->angle[1], sm.data->angle[2]);
// 	}

// 	return 0;
// }
