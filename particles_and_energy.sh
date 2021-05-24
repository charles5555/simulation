#!/bin/bash

gnuplot -e "set term png enhanced linewidth 2 fontscale 1.75; set output  'plot.png'; set ylabel '{/Symbol D}(t)'; set xlabel 'time'; plot 'outputdata.dat' using 1:2 w l ls 1 title '{/Symbol D}_1', 'outputdata.dat' using 1:5 w l ls 2 title '{/Symbol D}_2', 'outputdata.dat' using 1:8 w l ls 3 title '{/Symbol D}_3', 'outputdata.dat' using 1:11 w l ls 4 title '{/Symbol D}_4', 'outputdata.dat' using 1:23 w l ls 5 title '{/Symbol D}_8'"

gnuplot -e "set term png enhanced linewidth 2 fontscale 1.75; set output  'plot1.png'; set ylabel 'g_M(t)'; set xlabel 'time'; plot 'outputdata.dat' using 1:3 w l ls 1 title 'g_1', 'outputdata.dat' using 1:6 w l ls 2 title 'g_2', 'outputdata.dat' using 1:9 w l ls 3 title 'g_3', 'outputdata.dat' using 1:12 w l ls 4 title 'g_4', 'outputdata.dat' using 1:24 w l ls 5 title 'g_8'"

gnuplot -e "set term png enhanced linewidth 2 fontscale 1.75; set output  'plot2.png'; set ylabel '{/Symbol d}(t)'; set xlabel 'time'; plot 'outputdata.dat' using 1:4 w l ls 1 title '{/Symbol d}_1', 'outputdata.dat' using 1:7 w l ls 2 title '{/Symbol d}_2', 'outputdata.dat' using 1:10 w l ls 3 title '{Symbol d}_3', 'outputdata.dat' using 1:13 w l ls 4 title '{/Symbol d}_4', 'outputdata.dat' using 1:25 w l ls 5 title '{/Symbol d}_8'"





