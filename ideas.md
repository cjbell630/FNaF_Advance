Ideas:

FnaF theoretical gameplay loop:

* BMP background mode
* Load office and default background menus into memory (so all of the screens will be ready to be displayed)
	* There are 11 rooms + the office, and they honestly don't look that bad at 4bpp, so theoretically that would be plenty of colors for the backgrounds, and you could divide the office into two screens for 32 colors (possibly, idk)
* Apply static effect by inserting random greys into pallette (might take a lot of tweaking but should totally be possible)
	* Worst case scenario, you can just make a static sprite thing
* Ininitialize AI
* Upon anim location change, boost static to mask, load new image into memory, display new image, unboost static
* Possible controls:
	* L and R to scroll
	* A and B to operate door and light (the orientation should be intuitive)
	* Select to open camera (maybe also down for faster controls)
	* Dpad to navigate screens (will have to make an internal map, should be simple enough)
	* Select to close camera (maybe also LRAB etc for faster controls)
	* L+R to honk Freddy's nose :)
* It looks like at any point in time, you can see 2/3 of the office on-screen, so that means:
	* (2/3)*officeHorizReso = 240 -> 360
	* So the office should be 360px wide and 160px tall
	* Flat horizontal scrolling looks fine at that resolution
	* Looks alright at 4bpp 16 colors, should improve if I remove the buttons and fan and make them sprites
