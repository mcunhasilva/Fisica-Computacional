#set terminal wxt size 1024,720
#set terminal svg size 1024,720
#set output "poisson_2d_with_charges.svg"
#set terminal svg size 600,400 dynamic enhanced fname 'arial'  fsize 10 mousing name "Poisson_2D" butt dashlength 1.0 
set macros

#unset surface

#set label "P2D - p(x,y) = sin(xy)" at screen 0.7, 0.9
set xlabel 'x'
set ylabel 'y'
set zlabel 'V(x,y)'

#Cor
#color(x,y) = 10. * (1.1 + sin((x-20.)/5.)*cos((y-20.)/10.))

#PLOT SIMPLES 3D

set mapping cartesian
set view 60,30,1,1
set auto
set isosamples 60
set hidden3d
splot "Poisson_2d_charge.dat" using 1:2:3 with points lt 2 notitle


#HEAT MAP

#set title "Poisson (3D Heat Map)" offset 0,1

#set view map
#set ylabel norotate offset -1,0

#set contour base
#set dgrid3d
#set pm3d interpolate 0,0

#splot 'Poisson_2d_charge.dat' using 1:2:3 with pm3d


#set output
#pause -1
pause mouse button3, keypress
