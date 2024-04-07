# Auto generate program shortcuts based on qmk keymap

Easy intuitive (and nice to visualize) way to layout
your qmk combos based on position of the key instead
of the value assigned to it, this allows you to modify
your keymap without breaking your combos,
you just have to run the program "gencombos"
to autogenerate "combos.def".
As a bonus you can auto generate other programs mappings,
now you don't have to tediously go to each configuration
file and change each mapping one by one.
This code was rushed to meet my needs, therefore alot
of stuff is hard coded, like the directory and
name of the keymap. I'll fix it whenever I get the time.

As of now this covers generating:

combos.def      for qmk combos
.vimrc          (only noremap)
vimium extention mappings

