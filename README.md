# Tiny-Timer

This is a 25 minute work timer in C++ with the [WxWidgets 3.0.5](https://wxwidgets.org) toolkit.

Visual Studo solution is provided but the code should be usuable on any WxWidgets platform with a modern C++ compiler.

## HOWO

- When the application is opened an icon will appear in the system tray.
- There are three menu options: `Start / Pause`, `Reset` and `Quit`.
- Selecting `Start` will begin a countdown for 25 minutes.
- Hover over the icon to see how many minutes and seconds remain in the tooltip.
- `Pause` will pause the timer and also allow `Reset` to work
- When the timer is finished an alert modal will display

## TODO

- [ ] Replace the Event table with the `Connect` method. See: https://zetcode.com/gui/wxwidgets/events/

## Hacking

- This solution is compatible with Visual Studio 2010 Express or newer.
- Set the environment `WXWIN` to point to the WxWidgets 3.0.5 source code.
- `Debug` is dynamically-linked and `Release` is linked statically.
