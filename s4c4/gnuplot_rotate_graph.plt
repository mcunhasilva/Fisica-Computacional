set terminal gif animate delay 5 loop 0 optimize
set output "poisson2d_surface_rot2.gif"
set macros

#unset surface

set label "P2D - p(x,y) = sin(xy)" at screen 0.7, 0.9
set xlabel 'x'
set ylabel 'y'
set zlabel 'V(x,y)'

n = 360
do for [i=1:n] {
   set view 65, i*360/n
   splot "Poisson_2d.dat" using 1:2:3 with lines lt 2 notitle
}

set output
#pause -1
#pause mouse button3,keypress
