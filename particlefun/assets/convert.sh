#!/bin/sh


# Sprites
# grit pointer.png -ftb -fh! -gTFF00FF -gt -gB8 -m!
grit particle.png -ftb -fh! -gT000000 -gt -gB8 -m!
grit circ.png -ftb -fh! -gT000000 -gt -gB8 -m!
grit ball.png -ftb -fh! -gT000000 -gt -gB8 -m!
grit ship.png  -ftb -fh! -gT000000 -gt -gB8 -m!
grit ship-export.png  -ftb -fh! -gT000000 -gt -gB8 -m!
grit blueball.png -ftb -fh! -gTFF00FF -gt -gB8 -m!
# # grit pp.png -ftb -fh! -gT000000 -gt -gB8 -m!


for file in *.bin; do
    mv -- "$file" "${file%.bin}"
done

mv *.pal *.img ../nitrofiles/sprite


# # Backgrounds
# grit colmap.png -ftb -fh! -gTFF00FF -gt -gB8 -mR8 -mLs
# grit tiles.png -ftb -fh! -gTFFF1E8 -gt -gB8 -mR8 -mLs
# # grit layer3-copy.png -ftb -fh! -gTFF00FF -gt -gB8 -mR8 -mLs
# grit layer3-copy.png -ftb -fh! -gTFF00FF -gt -gB8 -mR8 -mLs
# # grit pp.png -ftb -fh! -gT000000 -gt -gB8 -m!
# grit algorave-text-empty.png -ftb -fh! -gTFF00FF -gt -gB8 -mR8 -mLs
# grit pp.png -ftb -fh! -gT000000 -gt -gB8 -mR8 -mLs


# for file in *.bin; do
#     mv -- "$file" "${file%.bin}"
# done

# mv *.pal *.img *.map ../nitrofiles/bg


# # Font
# grit default.png -ftb -fh! -gTFF00FF -gt -gB8 -m!

# for file in *.bin; do
#     mv -- "$file" "${file%.bin}"
# done

# for file in *.img; do
#     mv -- "$file" "${file%.img}".fnt
# done

# mv *.pal *.fnt ../nitrofiles/fnt
