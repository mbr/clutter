#include "clutterclockwidget.h"

G_DEFINE_TYPE (ClutterClockWidget, clutter_clock_widget, CLUTTER_TYPE_DESKTOP_WIDGET)

static void clutter_clock_widget_class_init(ClutterClockWidgetClass *klass) {
	klass->parent_class.on_expose = clutter_clock_widget_real_on_expose;
}

static void clutter_clock_widget_init(ClutterClockWidget *self) {
	/* "constructor" */
}

gboolean clutter_clock_widget_real_on_expose(ClutterDesktopWidget *self, GdkEventExpose *event) {
	g_debug("ClockWidget on expose called");
	ClutterDesktopWidgetClass *parent_class = g_type_class_peek_parent(CLUTTER_CLOCK_WIDGET_GET_CLASS(self));

	/* draw transparent background */
	parent_class->on_expose(self, event);

	cairo_t *cr = clutter_desktop_widget_get_context(self);
	cairo_set_source_rgb(cr, 0.5,0,0);
	cairo_paint(cr);
	cairo_destroy(cr);

	/* draw clock */
	return TRUE;
}

ClutterClockWidget *clutter_clock_widget_new(const gchar *themedir) {
	ClutterClockWidget *obj = g_object_new(CLUTTER_TYPE_CLOCK_WIDGET, NULL);

	obj->themedir = themedir;
	return obj;
}
