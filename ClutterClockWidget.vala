errordomain IOError {
	COULD_NOT_LOAD
}

Cairo.ImageSurface load_svg(string filename, int width, int height) throws IOError {
	Gdk.Pixbuf pb;
	try {
		pb = Rsvg.pixbuf_from_file_at_size(filename, width, height);
	} catch (GLib.Error e) {
		stderr.printf("Error loading %s: %s", filename, e.message);
		throw new IOError.COULD_NOT_LOAD("SVG load error");
	}
	if (null == pb) {
		stderr.printf("NULL result\n");
		throw new IOError.COULD_NOT_LOAD("SVG load error");
	}

	Cairo.Format imgformat = Cairo.Format.RGB24;
	if (pb.has_alpha) imgformat = Cairo.Format.ARGB32;

	Cairo.ImageSurface s = new Cairo.ImageSurface(imgformat, pb.get_width(), pb.get_height());
	Cairo.Context cr = new Cairo.Context(s);
	Gdk.cairo_set_source_pixbuf(cr, pb, 0, 0);
	cr.paint();

	return s; 
}

class ClutterClockWidget : ClutterDesktopWidget {
	protected string theme_dir;

	protected Cairo.ImageSurface clock_face;
	protected Cairo.ImageSurface clock_drop_shadow;
	protected Cairo.ImageSurface clock_face_shadow;
	protected Cairo.ImageSurface clock_frame;
	protected Cairo.ImageSurface clock_glass;
	protected Cairo.ImageSurface clock_marks;
	protected Cairo.ImageSurface clock_minute_hand;
	protected Cairo.ImageSurface clock_minute_hand_shadow;
	protected Cairo.ImageSurface clock_second_hand;
	protected Cairo.ImageSurface clock_second_hand_shadow;
	
	public ClutterClockWidget(string theme_dir) {
		this.theme_dir = theme_dir;
		this.size_allocate.connect(this.on_allocation_changed);
	}

	public void on_allocation_changed() {
		this.reload_theme();
	}

	public void reload_theme() {
		string clock_face_filename = this.theme_dir + "/clock-face.svg";
		string clock_drop_shadow_filename = this.theme_dir + "/clock-drop-shadow.svg";
		string clock_face_shadow_filename = this.theme_dir + "/clock-face-shadow.svg";
		string clock_frame_filename = this.theme_dir + "/clock-frame.svg";
		string clock_glass_filename = this.theme_dir + "/clock-glass.svg";
		string clock_marks_filename = this.theme_dir + "/clock-marks.svg";
		string clock_minute_hand_filename = this.theme_dir + "/clock-minute-hand.svg";
		string clock_minute_hand_shadow_filename = this.theme_dir + "/clock-minute-hand-shadow.svg";
		string clock_second_hand_filename = this.theme_dir + "/clock-second-hand-shadow.svg";
		string clock_second_hand_shadow_filename = this.theme_dir + "/clock-second-hand-shadow.svg";

		try {
			clock_face = load_svg(clock_face_filename, this.allocation.width, this.allocation.height);
			clock_drop_shadow = load_svg(clock_drop_shadow_filename, this.allocation.width, this.allocation.height);
			clock_face_shadow = load_svg(clock_face_shadow_filename, this.allocation.width, this.allocation.height);
			clock_frame = load_svg(clock_frame_filename, this.allocation.width, this.allocation.height);
			clock_glass = load_svg(clock_glass_filename, this.allocation.width, this.allocation.height);
			clock_marks = load_svg(clock_marks_filename, this.allocation.width, this.allocation.height);
			clock_minute_hand = load_svg(clock_minute_hand_filename, this.allocation.width, this.allocation.height);
			clock_minute_hand_shadow = load_svg(clock_minute_hand_shadow_filename, this.allocation.width, this.allocation.height);
			clock_second_hand = load_svg(clock_second_hand_filename, this.allocation.width, this.allocation.height);
			clock_second_hand_shadow = load_svg(clock_second_hand_shadow_filename, this.allocation.width, this.allocation.height);
		} catch(Error e) {
			stderr.printf("Error while loading clock theme: %s", e.message);
		}
	}

	public override bool on_expose() {
		base.on_expose();

		Cairo.Context cr = Gdk.cairo_create(this.window);
		cr.set_source_surface(clock_drop_shadow, 0, 0);
		cr.paint();

		cr.set_source_surface(clock_face, 0, 0);
		cr.paint();

		cr.set_source_surface(clock_marks, 0, 0);
		cr.paint();

		/* draw minute hand */
		/* draw second hand */

		cr.set_source_surface(clock_glass, 0, 0);
		cr.paint();

		cr.set_source_surface(clock_frame, 0, 0);
		cr.paint();

		return false;
	}
}
