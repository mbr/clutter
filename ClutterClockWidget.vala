errordomain IOError {
	COULD_NOT_LOAD
}

Rsvg.Handle load_svg(string filename) throws IOError {
	Rsvg.Handle pb;
	try {
		pb = new Rsvg.Handle.from_file(filename);
	} catch (GLib.Error e) {
		stderr.printf("Error loading %s: %s", filename, e.message);
		throw new IOError.COULD_NOT_LOAD("SVG load error");
	}
	if (null == pb) {
		stderr.printf("NULL result\n");
		throw new IOError.COULD_NOT_LOAD("SVG load error");
	}

	return pb; 
}

class ClutterClockWidget : ClutterDesktopWidget {
	protected enum ClockParts {
		FACE = 0,
		DROP_SHADOW,
		FACE_SHADOW,
		FRAME,
		GLASS,
		MARKS,
		HOUR_HAND,
		HOUR_HAND_SHADOW,
		MINUTE_HAND,
		MINUTE_HAND_SHADOW,
		SECOND_HAND,
		SECOND_HAND_SHADOW,
		END
	}

	protected const string[] theme_filenames = {
		"clock-face.svg",
		"clock-drop-shadow.svg",
		"clock-face-shadow.svg",
		"clock-frame.svg",
		"clock-glass.svg",
		"clock-marks.svg",
		"clock-hour-hand.svg",
		"clock-hour-hand-shadow.svg",
		"clock-minute-hand.svg",
		"clock-minute-hand-shadow.svg",
		"clock-second-hand-shadow.svg",
		"clock-second-hand-shadow.svg"
	};

	protected string theme_dir;

	enum ClockLayers {
		FRONT = 0,
		BACK,
		HOUR_HAND,
		MINUTE_HAND,
		SECOND_HAND,
		END
	}

	protected Cairo.ImageSurface[] layers;
	
	protected const int source_width_px = 100;
	protected const int source_height_px = 100;
	protected GLib.TimeVal current_time;

	public ClutterClockWidget(string theme_dir) {
		this.theme_dir = theme_dir;
		this.size_allocate.connect(this.on_allocation_changed);
	}

	public void refresh_time() {
		current_time.get_current_time();
	}

	public void on_allocation_changed() {
		reload_theme();
		refresh_time();
	}

	public void reload_theme() {
		Rsvg.Handle[] theme = new Rsvg.Handle[ClockParts.END];

		int width = this.allocation.width,
		    height = this.allocation.height;

		for(int i = 0; i < ClockParts.END; ++i) {
			try {
				theme[i] = load_svg(theme_dir + "/" + theme_filenames[i]);
			} catch(Error e) {
				stderr.printf("Error while loading clock theme file %s: %s", theme_filenames[i], e.message);
				return;
			}
		}

		/* initialize layers */
		layers = new Cairo.ImageSurface[ClockParts.END];
		for(int i = 0; i < ClockLayers.END; ++i) {
			layers[i] = new Cairo.ImageSurface(Cairo.Format.ARGB32, width, height);
		}

		Cairo.Context cr;

		cr = new Cairo.Context(layers[ClockLayers.BACK]);
		cr.scale(width/source_width_px, height/source_height_px);
		theme[ClockParts.DROP_SHADOW].render_cairo(cr);
		theme[ClockParts.FACE].render_cairo(cr);
		theme[ClockParts.MARKS].render_cairo(cr);

		cr = new Cairo.Context(layers[ClockLayers.FRONT]);
		cr.scale(width/source_width_px, height/source_height_px);
		theme[ClockParts.GLASS].render_cairo(cr);
		theme[ClockParts.FRAME].render_cairo(cr);

		/* prepare hands */
		cr = new Cairo.Context(layers[ClockLayers.HOUR_HAND]);
		cr.translate(width/2, height/2);
		cr.scale(width/source_width_px, height/source_height_px);
		theme[ClockParts.HOUR_HAND_SHADOW].render_cairo(cr);
		theme[ClockParts.HOUR_HAND].render_cairo(cr);

		cr = new Cairo.Context(layers[ClockLayers.MINUTE_HAND]);
		cr.translate(width/2, height/2);
		cr.scale(width/source_width_px, height/source_height_px);
		theme[ClockParts.MINUTE_HAND_SHADOW].render_cairo(cr);
		theme[ClockParts.MINUTE_HAND].render_cairo(cr);

		cr = new Cairo.Context(layers[ClockLayers.SECOND_HAND]);
		cr.translate(width/2, height/2);
		cr.scale(width/source_width_px, height/source_height_px);
		theme[ClockParts.SECOND_HAND_SHADOW].render_cairo(cr);
		theme[ClockParts.SECOND_HAND].render_cairo(cr);
	}

	public override bool on_expose() {
		/* recalculate time */
		base.on_expose();

		/* get local time */
		GLib.Time local = GLib.Time.local(current_time.tv_sec);
		double second = (local.second + (current_time.tv_usec/1000000.0)) % 60;

		stderr.printf("%d:%d:%f\n", local.hour, local.minute, second);

		int width = this.allocation.width,
		    height = this.allocation.height;

		Cairo.Context cr;

		cr = Gdk.cairo_create(this.window);
		cr.set_source_surface(layers[ClockLayers.BACK], 0, 0);
		cr.paint();

		/* draw hour hand */
		cr.save();
		cr.translate(width/2, height/2);
		cr.rotate(((local.hour%12)-3) * (Math.PI*2.0/12.0));
		cr.translate(-width/2, -height/2);
		cr.set_source_surface(layers[ClockLayers.HOUR_HAND], 0, 0);
		cr.paint();
		cr.restore();

		/* draw minute hand */
		cr.save();
		cr.translate(width/2, height/2);
		cr.rotate(((local.minute)-15) * (Math.PI*2.0/60.0));
		cr.translate(-width/2, -height/2);
		cr.set_source_surface(layers[ClockLayers.MINUTE_HAND], 0, 0);
		cr.paint();
		cr.restore();

		/* draw second hand */
		cr.save();
		cr.translate(width/2, height/2);
		cr.rotate(((second)-15.0) * (Math.PI*2.0/60.0));
		cr.translate(-width/2, -height/2);
		cr.set_source_surface(layers[ClockLayers.SECOND_HAND], 0, 0);
		cr.paint();
		cr.restore();

		cr.set_source_surface(layers[ClockLayers.FRONT], 0, 0);
		cr.paint();

		return false;
	}
}
