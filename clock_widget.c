#include <gdk/gdk.h>
#include <gtk/gtk.h>
#include <cairo/cairo.h>
#include <math.h>

#include "clutterclockwidget.h"

#if !G_DEBUG
#define debug(...)
#else
#define debug(...) g_debug(__VA_ARGS__)
#endif

int main(int argc, char **argv) {
	gtk_init(&argc, &argv);

	ClutterClockWidget *clock = clutter_clock_widget_new("example_theme");

	gtk_widget_show_all(GTK_WIDGET(clock));
	gtk_main();

	return 0;
}
