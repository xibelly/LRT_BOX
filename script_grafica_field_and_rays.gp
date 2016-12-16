plot "box.dat" u 1:2 title "f(x,y)"
set terminal png
set output "grafica_field_rays_theta0.png" 
set pointsize 1.5
set xlabe 'x'
set ylabe 'y'
set key top left
replot "rays_theta0.dat" u 1:2 title "rays_theta0"

plot "box.dat" u 1:2 title "f(x,y)"
set terminal png
set output "grafica_field_rays_theta80.png" 
set pointsize 1.5
set xlabe 'x'
set ylabe 'y'
set key top left
replot "rays_theta80.dat" u 1:2 title "rays_theta80"

plot "box.dat" u 1:2 title "f(x,y)"
set terminal png
set output "grafica_field_rays_theta160.png" 
set pointsize 1.5
set xlabe 'x'
set ylabe 'y'
set key top left
replot "rays_theta160.dat" u 1:2 title "rays_theta160"

plot "box.dat" u 1:2 title "f(x,y)"
set terminal png
set output "grafica_field_rays_theta240.png" 
set pointsize 1.5
set xlabe 'x'
set ylabe 'y'
set key top left
replot "rays_theta240.dat" u 1:2 title "rays_theta240"

plot "box.dat" u 1:2 title "f(x,y)"
set terminal png
set output "grafica_field_rays_theta320.png" 
set pointsize 1.5
set xlabe 'x'
set ylabe 'y'
set key top left
replot "rays_theta320.dat" u 1:2 title "rays_theta320" 