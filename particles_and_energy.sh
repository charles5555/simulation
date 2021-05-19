#!/bin/bash

gnuplot -e "set term png enhanced linewidth 2 fontscale 1.75; set output  'plot.png'; set ylabel 'g'; set xlabel 'time'; set xrange [0:3]; plot 'outputdata.dat' using 1:2 w l ls 1 title 'g_1', 'outputdata.dat' using 1:4 w l ls 2 title 'g_2', 'outputdata.dat' using 1:6 w l ls 3 title 'g_3', 'outputdata.dat' using 1:8 w l ls 4 title 'g_4'"

gnuplot -e "set term png enhanced linewidth 2 fontscale 1.75; set output  'plot1.png'; set ylabel 'g*e'; set xlabel 'time'; set xrange [0:3]; plot 'outputdata.dat' using 1:3 w l ls 1 title 'g_1', 'outputdata.dat' using 1:5 w l ls 2 title 'g_2', 'outputdata.dat' using 1:7 w l ls 3 title 'g_3', 'outputdata.dat' using 1:9 w l ls 4 title 'g_4'"


