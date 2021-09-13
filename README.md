# Asking about flowers

This is a project aiming to convert content from [The Ur-Quan Masters](http://sc2.sourceforge.net/) into different, more easily parseable (or usable) formats, using a variety of (homebrewn) tools.

## License

As per UQM's original content license, all content in this repository is licensed under [Creative Commons by-nc-sa 2.5](https://creativecommons.org/licenses/by-nc-sa/2.5/). TypeScript code is licensed under the MIT license.

## Command reference

* `npm run build-animations` - Builds APNG files for all `comm/**/*.ani` files, and places them in `comm/<...>/anim_apng_out/`
* `npm run compute-line-timings` - Computes line timings for all aliens under `comm` and builds nice line-by-line .json files containing all line timings as well as which dialogue is said at that line, and which audio file is used.
* `npm run parse-c-and-extract-anim` - Parses all `comm/**/*.c` files, extracts the animation definitions from the LOCDATA struct in there, and updates the `.ani` files next to these files to include the UQMAnimationTool-compatible animation directives. This command won't work for folders where there's no `.ani` file present (e.g. `yehatrebels`).
* `npm run generate-fonts` - Parses all `fonts/*.fon` files and generates XNA style font images.
