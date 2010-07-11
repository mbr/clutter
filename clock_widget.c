#include <gdk/gdk.h>
#include <gtk/gtk.h>
#include <cairo/cairo.h>
#include <math.h>

#include "clutterdesktopwidget.h"

#if !G_DEBUG
#define debug(...)
#else
#define debug(...) g_debug(__VA_ARGS__)
#endif

int main(int argc, char **argv) {
	gtk_init(&argc, &argv);

	ClutterDesktopWidget *w = clutter_desktop_widget_new("My Desktop Widget");

	gtk_widget_show_all(GTK_WIDGET(w));
	gtk_main();

	return 0;
}
