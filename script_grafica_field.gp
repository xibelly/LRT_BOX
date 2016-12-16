set terminal png
set output "grafica_tophatfield.png" 
set pointsize 1.5
set xlabe 'x'
set ylabe 'y'
set zlabe 'f(x,y)'
set key top left
splot "box.dat" u 1:2:3 title "f(x,y)" 