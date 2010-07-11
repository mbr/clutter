#ifndef UTIL_H
#define UTIL_H 

#include <gtk/gtk.h>
#include <math.h>

void clutter_set_window_widgety(GtkWindow *window, gboolean enabled);
gboolean clutter_set_widget_colormap(GtkWidget *widget, gboolean enabled);

#define M_PI 3.141592653589793238462643
#define M_SQRT2 1.4142135623730950488016887

#endif /* UTIL_H */
