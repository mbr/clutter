int main(string[] args) {
	Gtk.init(ref args);
	ClutterClockWidget w = new ClutterClockWidget("theme");
	w.show();
	Gtk.main();
	return 0;
}
