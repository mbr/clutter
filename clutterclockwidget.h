#ifndef CLOCK_WIDGET_H
#define CLOCK_WIDGET_H

#include "clutterdesktopwidget.h"

#define CLUTTER_TYPE_CLOCK_WIDGET (clutter_clock_widget_get_type())
#define CLUTTER_CLOCK_WIDGET(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), CLUTTER_TYPE_CLOCK_WIDGET, ClutterClockWidget))
#define CLUTTER_IS_CLOCK_WIDGET(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj), CLUTTER_TYPE_CLOCK_WIDGET))
#define CLUTTER_CLOCK_WIDGET_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST((klass), CLUTTER_TYPE_CLOCK_WIDGET, ClutterClockWidgetClass))
#define CLUTTER_IS_CLOCK_WIDGET_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE((klass), CLUTTER_TYPE_CLOCK_WIDGET))
#define CLUTTER_CLOCK_WIDGET_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS((obj), CLUTTER_TYPE_CLOCK_WIDGET, ClutterClockWidgetClass))

typedef struct _ClutterClockWidget ClutterClockWidget;
typedef struct _ClutterClockWidgetClass ClutterClockWidgetClass;

struct _ClutterClockWidget {
	ClutterDesktopWidget parent;

	const gchar *themedir;
	/* <private> */
};

struct _ClutterClockWidgetClass {
	ClutterDesktopWidgetClass parent_class;

	/* <private> */
};

gboolean clutter_clock_widget_real_on_expose(ClutterDesktopWidget *self, GdkEventExpose *event);

GType clutter_clock_widget_get_type(void);
ClutterClockWidget *clutter_clock_widget_new(const gchar *themedir);

#endif /* CLOCK_WIDGET_H */
