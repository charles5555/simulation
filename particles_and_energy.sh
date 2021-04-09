#!/bin/bash

gnuplot -e "set term png enhanced linewidth 2 fontscale 1.75; set output  'plot.png'; plot 'outputdata.dat' using 1:2 w l ls 1 title 'base'"
