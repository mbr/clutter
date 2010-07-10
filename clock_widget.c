#include <gdk/gdk.h>
#include <gtk/gtk.h>
#include <cairo/cairo.h>
#include <math.h>

#if !G_DEBUG
#define debug(...)
#else
#define debug(...) g_debug(__VA_ARGS__)
#endif

//static double pi;

static gboolean set_alpha(GtkWidget *widget, gboolean alpha) {
	GdkScreen *screen = gtk_widget_get_screen(widget);
	GdkColormap *colormap_rgb = gdk_screen_get_rgb_colormap(screen);
	GdkColormap *colormap_rgba = gdk_screen_get_rgba_colormap(screen);

	gboolean alpha_support = FALSE;

	if (alpha) {
		if (!colormap_rgba) {
			debug("No alpha support!");
			gtk_widget_set_colormap(widget, colormap_rgb);
		} else {
			debug("Enabling alpha support.");
			gtk_widget_set_colormap(widget, colormap_rgba);
		}
	} else {
		debug("No alpha support requested");
		gtk_widget_set_colormap(widget, colormap_rgb);
	}

	return alpha_support && alpha;
}

typedef struct {
	GtkWidget *window;
	gboolean alpha_enabled;

	gulong handler_screen_changed;
	gulong handler_exposed;
} deskwidget_t;

static void widgety_screen_changed(GtkWidget *widget, GdkScreen *old_screen, gpointer user_data) {
	set_alpha(widget, TRUE);
}

static gboolean widgety_expose(GtkWidget *widget, GdkEventExpose *event, gpointer user_data) {
	debug("Expose");
	cairo_t *cr = gdk_cairo_create(widget->window);
	cairo_set_source_rgba(cr, 1.0, 1.0, 1.0, 0.5);

	cairo_set_operator(cr, CAIRO_OPERATOR_SOURCE);
	cairo_paint(cr);
	cairo_destroy(cr);

	return FALSE;
}

void deskwidget_make_widgety(deskwidget_t *deskwidget) {
	GtkWindow *window = GTK_WINDOW(deskwidget->window);

	gtk_window_set_skip_taskbar_hint(window, TRUE);
	gtk_window_set_skip_pager_hint(window, TRUE);
	gtk_window_set_keep_below(window, TRUE);
	gtk_window_set_decorated(window, FALSE);
	gtk_widget_set_app_paintable(deskwidget->window, TRUE);

	deskwidget->handler_screen_changed = g_signal_connect(G_OBJECT(window), "screen-changed",
	                                                         G_CALLBACK(widgety_screen_changed), NULL);
	deskwidget->handler_exposed = g_signal_connect(G_OBJECT(window), "expose-event",
	                                               G_CALLBACK(widgety_expose), NULL);
	deskwidget->alpha_enabled = set_alpha(deskwidget->window, TRUE);
}

void deskwidget_make_unwidgety(deskwidget_t *deskwidget) {
	GtkWindow *window = GTK_WINDOW(deskwidget->window);

	gtk_window_set_skip_taskbar_hint(window, FALSE);
	gtk_window_set_skip_pager_hint(window, FALSE);
	gtk_window_set_keep_below(window, FALSE);
	gtk_window_set_decorated(window, TRUE);
	gtk_widget_set_app_paintable(deskwidget->window, FALSE);
	g_signal_handler_disconnect(G_OBJECT(window), deskwidget->handler_screen_changed);
	deskwidget->alpha_enabled = set_alpha(deskwidget->window, FALSE);
}

deskwidget_t *deskwidget_new() {
	deskwidget_t* deskwidget = g_new0(deskwidget_t, 1);
	deskwidget->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	return deskwidget;
}

int main(int argc, char **argv) {
//	pi = acos(-1);

	gtk_init(&argc, &argv);

	deskwidget_t *deskwidget = deskwidget_new();

	deskwidget_make_widgety(deskwidget);
	gtk_widget_show_all(deskwidget->window);
	gtk_main();

	return 0;
}
