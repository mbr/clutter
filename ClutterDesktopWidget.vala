class ClutterDesktopWidget : Gtk.Window {
	public ClutterDesktopWidget () {

		/* set widget properties */
		this.set_skip_taskbar_hint(true);
		this.set_skip_pager_hint(true);
		this.set_keep_below(true);
		this.set_decorated(false);
		this.set_app_paintable(true);
		this.stick();

		/* transparency */
		this.set_rgba_colormap();

		/* signals */
		this.screen_changed.connect(this.set_rgba_colormap);
		this.expose_event.connect(this.on_expose);
	}

	public bool on_expose() {
		Cairo.Context cr = Gdk.cairo_create(this.window);
		cr.set_source_rgba(1.0, 1.0, 1.0, 0.5);
		cr.set_operator(Cairo.Operator.SOURCE);
		cr.paint();

		return false;
	}

	public void set_rgba_colormap() {
		Gdk.Colormap rgba = this.get_screen().get_rgba_colormap();
		if (null == rgba) stderr.printf("Could not set rgba colormap\n");
		else this.set_colormap(rgba);
	}
}

int main(string[] args) {
	Gtk.init(ref args);
	ClutterDesktopWidget w = new ClutterDesktopWidget();
	w.show();
	Gtk.main();
	return 0;
}
