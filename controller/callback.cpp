#include "callback.h"

gint on_main_window_delete_event(GtkWidget *Widget, GdkEvent *event, gpointer data)
{
	g_print("Deleted\n");
//	return TRUE;
	on_main_window_destroy((GtkObject *)Widget, data);
	return 0;
}

void on_main_window_destroy (GtkObject *object, gpointer user_data)
{
	printf("destroy\n");
	gtk_main_quit();
}

gboolean
on_vscale_x_change_value(GtkRange        *range,
						 GtkScrollType    scroll,
						 gdouble          value,
						 gpointer         user_data)
{
	printf("hoge\n");
	return FALSE;
}
