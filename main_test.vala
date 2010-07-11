int main(string[] args) {
	Gtk.init(ref args);
	ClutterClockWidget w = new ClutterClockWidget("example-theme");
	w.show();
	Gtk.main();
	return 0;
}
