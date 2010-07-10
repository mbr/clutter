#include <gdk/gdk.h>
#include <gtk/gtk.h>
#include <cairo/cairo.h>
#include <math.h>

static double pi;

void make_widgety(GtkWindow *widget) {
	gtk_window_set_skip_taskbar_hint(widget, TRUE);
	gtk_window_set_skip_pager_hint(widget, TRUE);
	gtk_window_set_keep_below(widget, TRUE);
	gtk_window_set_decorated(widget, FALSE);
}

void make_unwidgety(GtkWindow *widget) {
	gtk_window_set_skip_taskbar_hint(widget, FALSE);
	gtk_window_set_skip_pager_hint(widget, FALSE);
	gtk_window_set_keep_below(widget, FALSE);
	gtk_window_set_decorated(widget, TRUE);
}

typedef struct {
	GtkWidget *drawing_area;
} clock_face_t;

void redraw_clock(clock_face_t *clock) {
	printf("Redrawing clock\n");
	cairo_t *cr = gdk_cairo_create(clock->drawing_area->window);

	/* apply proper coordinate transforms */
	cairo_scale(cr, clock->drawing_area->allocation.width,
	                clock->drawing_area->allocation.height);

	/* make background transparent */
	cairo_set_source_rgba(cr, 0, 0, 0, 0);
	cairo_set_operator(cr, CAIRO_OPERATOR_CLEAR);
	cairo_paint(cr);

	/* start with the background */
	cairo_arc(cr, 0.5, 0.5, 0.5, 0, 2*pi);
	cairo_set_source_rgb(cr, 0.5, 0.5, 0.5);
	cairo_fill(cr);

	cairo_destroy(cr);
}

gboolean clock_expose_event(GtkWidget *drawing_area, GdkEventExpose *event, clock_face_t *clock) {
	/* redraw clock: */
	redraw_clock(clock);

	return FALSE;
}

int main(int argc, char **argv) {
	pi = acos(-1);

	gtk_init(&argc, &argv);

	clock_face_t c;

	GtkWidget *widget;

	widget = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	c.drawing_area = gtk_drawing_area_new();

	/* initialize transparency */
	GdkScreen *screen = gtk_widget_get_screen(c.drawing_area);
	GdkColormap *rgba = gdk_screen_get_rgba_colormap(screen);
	gtk_widget_set_colormap(c.drawing_area, rgba);
	gtk_widget_set_app_paintable(c.drawing_area, TRUE);

	gtk_container_add(GTK_CONTAINER(widget), c.drawing_area);

	g_signal_connect(widget, "delete-event",
	                 G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(G_OBJECT (c.drawing_area), "expose_event",
	                 G_CALLBACK (clock_expose_event), &c);

//	make_widgety(GTK_WINDOW(widget));

	gtk_widget_show_all(widget);
	gtk_main();
	return 0;
}
