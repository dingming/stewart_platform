#ifndef CALLBACK_H
#define CALLBACK_H

#include <gtk/gtk.h>
//#include <gtkmm.h> 

gint
on_main_window_delete_event(GtkWidget	*Widget,
							GdkEvent	*event,
							gpointer	data);

void
on_main_window_destroy(GtkObject		*object,
					   gpointer	user_data);

gboolean
on_vscale_x_change_value(GtkRange        *range,
						 GtkScrollType    scroll,
						 gdouble          value,
						 gpointer         user_data);

gboolean
on_vscale_y_change_value(GtkRange        *range,
						 GtkScrollType    scroll,
						 gdouble          value,
						 gpointer         user_data);
gboolean
on_vscale_z_change_value(GtkRange        *range,
						 GtkScrollType    scroll,
						 gdouble          value,
						 gpointer         user_data);
gboolean
on_vscale_roll_change_value(GtkRange        *range,
						 GtkScrollType    scroll,
						 gdouble          value,
						 gpointer         user_data);
gboolean
on_vscale_pitch_change_value(GtkRange        *range,
						 GtkScrollType    scroll,
						 gdouble          value,
						 gpointer         user_data);
gboolean
on_vscale_yaw_change_value(GtkRange        *range,
						 GtkScrollType    scroll,
						 gdouble          value,
						 gpointer         user_data);


#endif
