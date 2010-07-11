#include "clutterdesktopwidget.h"
#include "util.h"

G_DEFINE_TYPE (ClutterDesktopWidget, clutter_desktop_widget, GTK_TYPE_WINDOW)

static gboolean on_expose(GtkWidget *widget, GdkEventExpose *event, gpointer user_data) {
	/* paint window transparent */
	
	cairo_t *cr = gdk_cairo_create(widget->window);
	cairo_set_source_rgba(cr, 1.0, 1.0, 1.0, 0.5);

	cairo_set_operator(cr, CAIRO_OPERATOR_SOURCE);
	cairo_paint(cr);
	cairo_destroy(cr);

	return FALSE;
}

static void on_screen_changed(GtkWidget *widget, GdkScreen *old_screen, gpointer user_data) {
	/* re-enable alpha */
	clutter_set_widget_colormap(widget, TRUE);
}

static void clutter_desktop_widget_class_init(ClutterDesktopWidgetClass *klass) {
	/* set up virtual method handler here, if needed */
}

static void clutter_desktop_widget_init(ClutterDesktopWidget *self) {
	clutter_set_window_widgety(GTK_WINDOW(self), TRUE);

	g_signal_connect(G_OBJECT(self), "screen-changed",
	                 G_CALLBACK(on_screen_changed), NULL); 
	g_signal_connect(G_OBJECT(self), "expose-event",
	                 G_CALLBACK(on_expose), NULL);
}

ClutterDesktopWidget *clutter_desktop_widget_new(const gchar* title) {
	ClutterDesktopWidget* w = g_object_new(CLUTTER_TYPE_DESKTOP_WIDGET, NULL);
	gtk_window_set_title(GTK_WINDOW(w), title);

	return w;
}
