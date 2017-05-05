ffmpeg -framerate 1 -pattern_type glob -i 'photo_*.jpg' -c:v libx264 -pix_fmt yuv420p out.mp4
