#!/bin/bash
gnuplot -e "set term png enhanced linewidth 2 fontscale 1.75; set output 'plot4.png'; plot 'outputdata.dat' using 1:2 w l ls 1 title 'n', 'outputdata.dat' using 1:5 w l ls 2, 'outputdata.dat' using 1:8 w l ls 3 notitle"
