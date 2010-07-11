#include "util.h"

gboolean clutter_set_widget_colormap(GtkWidget *widget, gboolean enabled) {
	GdkScreen *screen = gtk_widget_get_screen(widget);

	GdkColormap *colormap_rgb = gdk_screen_get_rgb_colormap(screen);
	if (! enabled) {
		/* non-alpha colormap requested */
		gtk_widget_set_colormap(widget, colormap_rgb);
		return TRUE;
	} else {
		GdkColormap *colormap_rgba = gdk_screen_get_rgba_colormap(screen);
		if (! colormap_rgba) return FALSE;

		gtk_widget_set_colormap(widget, colormap_rgba);
		return TRUE;
	}
}

void clutter_set_window_widgety(GtkWindow *window, gboolean enabled) {
	gtk_window_set_skip_taskbar_hint(window, enabled);
	gtk_window_set_skip_pager_hint(window, enabled);
	gtk_window_set_keep_below(window, enabled);
	gtk_window_set_decorated(window, ! enabled);
	gtk_widget_set_app_paintable(GTK_WIDGET(window), enabled);
	if (! clutter_set_widget_colormap(GTK_WIDGET(window), enabled)) {
		g_warning("Could not set alpha-colormap on widget.");
	}
}
