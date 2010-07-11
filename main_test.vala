int main(string[] args) {
	Gtk.init(ref args);
	ClutterDesktopWidget w = new ClutterDesktopWidget();
	w.show();
	Gtk.main();
	return 0;
}
