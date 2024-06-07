rem Please put ffmpeg.exe in this folder！
ffmpeg.exe -loop 1 -i lenna-500X500.png -c:v libx264 -t 10 -s 100x100 lenna-500X500.mp4
pause