#!/bin/bash

gnuplot -e "set term png enhanced linewidth 2 fontscale 1.75; set output 'plot_restriction_particle.png'; plot 'restrictionsdata.dat' using 1:2 w l ls 1 title 'particle restriction'"&&\
gnuplot -e "set term png enhanced linewidth 2 fontscale 1.75; set output 'plot_restriction_energy.png'; plot 'restrictionsdata.dat' using 1:3 w l ls 1 title 'particle restriction'"
