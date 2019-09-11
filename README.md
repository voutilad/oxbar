# about the fork
Are you looking for the real [oxbar](https://github.com/ryanflannery/oxbar.git)?

This is a fork where I'm going to play with making a non-X11 version,
specifically for leveraging the existing C code for collecting metrics.

---

# oxbar
oxbar is a X11 status bar for OpenBSD showing various system stats.
It has a configurable display and works out-of-the-box on most modern window
managers in an intuitive fashion.
oxbar supports FreeType font rendering and styling, true transparency & alpha
blending on all UI components (including the root window), and a simple
configuration format that can concisely support multiple themes.

It's motivated by the frequent complaints/threats I get about
my old xstatbar and its many hacks. Shaming works 'yo.

oxbar is released under an
[ISC license](https://github.com/ryanflannery/oxbar/blob/master/LICENSE)

![screenshot](images/fullscreen.png?raw=true)


# features
* True transparency support with a compositing window manager
   * I recommend compton (in ports) over xcompmgr (in base)
* FreeType fonts styled & rendered easily, with all font options
* Fully configurable display via the command line or config file
* Left/Right/Center aligned widgets, and any combination of those
* Configuration file supports multiple themes that can be chosen at runtime
* Types of stats supported:
   * Battery/AC status, progress bar, time remaining
   * Brightness level w/ progress bar (via Xrandr(3))
   * Volume level w/ progress bar
   * Number of processes
   * Memory usage & breakdown
   * CPUs usage & breakdown w/ or w/out charts
   * WiFi signal strength
   * Current date/time (is that a status?)
   * Others forthcoming


# more screenshots
oxbar's default look (with no options):
![default](images/theme-default.png?raw=true)

Other themes, all included in the file
[sample.oxbar.conf](sample.oxbar.conf):

**islands**: each widget is an island, with true transparency between
![islands](images/theme-islands.png?raw=true)

**islands-colorful**: like islands, but each widget is a different color
![islands-colorful](images/theme-islands-colorful.png?raw=true)

**minimal**: a dark, text only display
![minimal](images/theme-minimal.png?raw=true)

**pastels**: a pastel based theme with widgets tightly packed
![pastels](images/theme-pastels.png?raw=true)

**ryan**: what my setup looks like
![ryan](images/theme-ryan.png?raw=true)

**xstatbar**: looks just like it's predecessor
![xstatbar](images/theme-xstatbar.png?raw=true)


# installing
There is no port/package (yet), as oxbar is still under active development.
To build & install, you'll need to first install 2 dependencies, pango and
cairo, and then clone this repo and run `make install`.

Roughly:
```bash
 $ doas pkg_add pango cairo      # install dependencies (as root)
 $ make                          # build oxbar
 $ doas make install             # install globally (as root)
 -or-
 $ PREFIX=~/local make install   # install local to a user (or anywhere)
```


# usage
Full man page available here:
[oxbar(1)](http://htmlpreview.github.io/?https://raw.githubusercontent.com/ryanflannery/oxbar/master/man/oxbar.html).

`oxbar -H` also has a brief description of each command line flag.
See the sample configuration [sample.oxbar.conf](sample.oxbar.conf) for
examples, like the themes above.


# i liked xstatbar's look
You can achieve that using the included sample configuration file, saved as
`~/.oxbar.conf`, and run oxbar via:
```bash
oxbar xstatbar
```


# outstanding stuff, prioritized
See the [TODO](TODO) file for various TODO's present throughout the code.

In addition, more long-term stuff I'd like to do, by my priority...
* big refactor: make all widgets 100% config-driven... Basically, eliminate
  the need for individual widget code in `widgets/` entirely, and make them
  all configurable via a simple syntax. I know how to do most of this, and
  easily from a configuration standpoint, but not all. My current thoughts
  would make the configuration too verbose/lengthy, and impractical. Chew on
  this more, I will...
* gui: icons in the display could help condense it further
* stats: add collector for hw.sensors & a related widget
* stats: add a weather component...i like weather
* when using compton, need '--shadow-exclude 'name = "oxbar"' to disable
  shadow - how can i automate that?
