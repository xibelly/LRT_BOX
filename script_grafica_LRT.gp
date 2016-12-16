set terminal png
set output "grafica_field_rays_theta0.png" 
set pointsize 1.5
set ylabe 'Theta'
set xlabe 'R[f(x,y)]'
set key top left
plot "LRT.dat" u 1:2 title "LRT"
