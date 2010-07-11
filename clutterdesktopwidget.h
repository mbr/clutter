#ifndef DESKTOP_WIDGET_H
#define DESKTOP_WIDGET_H

/* Header automatically generated by  */

#include <gtk/gtk.h>

#define CLUTTER_TYPE_DESKTOP_WIDGET (clutter_desktop_widget_get_type())
#define CLUTTER_DESKTOP_WIDGET(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), CLUTTER_TYPE_DESKTOP_WIDGET, DesktopWidget))
#define CLUTTER_IS_DESKTOP_WIDGET(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj), CLUTTER_TYPE_DESKTOP_WIDGET))
#define CLUTTER_DESKTOP_WIDGET_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST((klass), CLUTTER_TYPE_DESKTOP_WIDGET, DesktopWidgetClass))
#define CLUTTER_IS_DESKTOP_WIDGET_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE((klass), CLUTTER_TYPE_DESKTOP_WIDGET))
#define CLUTTER_DESKTOP_WIDGET_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS((obj), CLUTTER_TYPE_DESKTOP_WIDGET, DesktopWidgetClass))

typedef struct _ClutterDesktopWidget ClutterDesktopWidget;
typedef struct _ClutterDesktopWidgetClass ClutterDesktopWidgetClass;

struct _ClutterDesktopWidget {
	GtkWindow parent;

	/* <private> */
};

struct _ClutterDesktopWidgetClass {
	GtkWindowClass parent_class;

	/* <private> */
};

GType clutter_desktop_widget_get_type(void);
ClutterDesktopWidget *clutter_desktop_widget_new();

#endif /* DESKTOP_WIDGET_H */
