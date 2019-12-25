# !/bin/bash
# Limpando tudo

clear

# Deletando Precedent Animation data

rm -r animation
mkdir animation


rm palette.png
rm video.gif
rm video.avi

# Rodando programa

gcc main.c -o main
./main

# Gerando videos e gifs

ffmpeg -i ./animation/img%06d.png -vf scale=900:-1:sws_dither=ed,palettegen palette.png
ffmpeg -framerate 40 -i ./animation/img%06d.png video.avi
ffmpeg -i video.avi -i palette.png -filter_complex "fps=40,scale=900:-1:flags=lanczos[x];[x][1:v]paletteuse" video.gif
