#!/bin/bash

gnuplot -e "set term png enhanced linewidth 2 fontscale 1.75;
set output  'plot.png';
set ylabel '{/Symbol D}(t)';
set xlabel 'time (1x10E-3) {/Symbol t}';
plot 'outputdata.dat' using 1:2 w l ls 1 notitle '{/Symbol D}_1',
'outputdata.dat' using 1:5 w l ls 2 notitle '{/Symbol D}_2',
'outputdata.dat' using 1:8 w l ls 3 notitle '{/Symbol D}_3',
'outputdata.dat' using 1:11 w l ls 4 notitle '{/Symbol D}_4',
'outputdata.dat' using 1:14 w l ls 5 notitle '{/Symbol D}_5',
'outputdata.dat' using 1:17 w l ls 6 notitle '{/Symbol D}_6',
'outputdata.dat' using 1:20 w l ls 7 notitle '{/Symbol D}_{7}',
'outputdata.dat' using 1:23 w l ls 8 notitle '{/Symbol D}_8',
'outputdata.dat' using 1:26 w l ls 9 notitle '{/Symbol D}_9',
'outputdata.dat' using 1:29 w l ls 10 notitle '{/Symbol D}_{10}',
'outputdata.dat' using 1:32 w l ls 11 notitle '{/Symbol D}_{11}',
'outputdata.dat' using 1:35 w l ls 12 notitle '{/Symbol D}_{12}',
'outputdata.dat' using 1:38 w l ls 13 notitle '{/Symbol D}_{13}',
'outputdata.dat' using 1:41 w l ls 14 notitle '{/Symbol D}_{14}',
'outputdata.dat' using 1:44 w l ls 15 notitle '{/Symbol D}_{15}',
'outputdata.dat' using 1:47 w l ls 16 notitle '{/Symbol D}_{16}',
'outputdata.dat' using 1:50 w l ls 17 notitle '{/Symbol D}_{17}',
'outputdata.dat' using 1:53 w l ls 18 notitle '{/Symbol D}_{18}',
'outputdata.dat' using 1:56 w l ls 19 notitle '{/Symbol D}_{19}',
'outputdata.dat' using 1:59 w l ls 20 notitle '{/Symbol D}_{20}',
'outputdata.dat' using 1:62 w l ls 21 notitle '{/Symbol D}_{21}',
'outputdata.dat' using 1:65 w l ls 22 notitle '{/Symbol D}_{22}',
'outputdata.dat' using 1:68 w l ls 23 notitle '{/Symbol D}_{23}',
'outputdata.dat' using 1:71 w l ls 24 notitle '{/Symbol D}_{24}',
'outputdata.dat' using 1:74 w l ls 25 notitle '{/Symbol D}_{25}',
'outputdata.dat' using 1:77 w l ls 26 notitle '{/Symbol D}_{26}',
'outputdata.dat' using 1:80 w l ls 27 notitle '{/Symbol D}_{27}'
"

gnuplot -e "set term png enhanced linewidth 2 fontscale 1.75; 
set output  'plot1.png'; 
set ylabel 'g_M(t)'; 
set xlabel 'time(1x10E-3){/Symbol t}'; 
plot 'outputdata.dat' using 1:3 w l ls 1 notitle 'g_1',
'outputdata.dat' using 1:6 w l ls 2 notitle 'g_2', 
'outputdata.dat' using 1:9 w l ls 3 notitle 'g_3', 
'outputdata.dat' using 1:12 w l ls 4 notitle 'g_4', 
'outputdata.dat' using 1:15 w l ls 5 notitle 'g_5',
'outputdata.dat' using 1:18 w l ls 6 notitle 'g_6',
'outputdata.dat' using 1:21 w l ls 7 notitle 'g_7',
'outputdata.dat' using 1:24 w l ls 8 notitle 'g_8',
'outputdata.dat' using 1:27 w l ls 9 notitle 'g_9',
'outputdata.dat' using 1:30 w l ls 10 notitle 'g_{10}',
'outputdata.dat' using 1:33 w l ls 11 notitle 'g_{11}',
'outputdata.dat' using 1:36 w l ls 12 notitle 'g_{12}',
'outputdata.dat' using 1:39 w l ls 13 notitle 'g_{13}',
'outputdata.dat' using 1:42 w l ls 14 notitle 'g_{14}',
'outputdata.dat' using 1:45 w l ls 15 notitle 'g_{15}',
'outputdata.dat' using 1:48 w l ls 16 notitle 'g_{16}',
'outputdata.dat' using 1:51 w l ls 17 notitle 'g_{17}',
'outputdata.dat' using 1:54 w l ls 18 notitle 'g_{18}',
'outputdata.dat' using 1:57 w l ls 19 notitle 'g_{19}',
'outputdata.dat' using 1:60 w l ls 20 notitle 'g_{20}',
'outputdata.dat' using 1:63 w l ls 21 notitle 'g_{21}',
'outputdata.dat' using 1:66 w l ls 22 notitle 'g_{22}',
'outputdata.dat' using 1:69 w l ls 23 notitle 'g_{23}',
'outputdata.dat' using 1:72 w l ls 24 notitle 'g_{24}',
'outputdata.dat' using 1:75 w l ls 25 notitle 'g_{25}',
'outputdata.dat' using 1:78 w l ls 26 notitle 'g_{26}',
'outputdata.dat' using 1:81 w l ls 27 notitle 'g_{27}'
"

gnuplot -e "set term png enhanced linewidth 2 fontscale 1.75;
set output  'plot2.png'; 
set ylabel '{/Symbol d}(t)'; 
set xlabel 'time(1x10E-3){/Symbol t}'; 
plot 'outputdata.dat' using 1:4 w l ls 1 notitle '{/Symbol d}_1', 
'outputdata.dat' using 1:7 w l ls 2 notitle '{/Symbol d}_2', 
'outputdata.dat' using 1:10 w l ls 3 notitle '{/Symbol d}_3', 
'outputdata.dat' using 1:13 w l ls 4 notitle '{/Symbol d}_4', 
'outputdata.dat' using 1:16 w l ls 5 notitle '{/Symbol d}_5',
'outputdata.dat' using 1:19 w l ls 6 notitle 'g_6',
'outputdata.dat' using 1:22 w l ls 7 notitle 'g_7',
'outputdata.dat' using 1:25 w l ls 8 notitle 'g_8',
'outputdata.dat' using 1:28 w l ls 9 notitle 'g_9',
'outputdata.dat' using 1:31 w l ls 10 notitle 'g_{10}',
'outputdata.dat' using 1:34 w l ls 11 notitle 'g_{11}',
'outputdata.dat' using 1:37 w l ls 12 notitle 'g_{12}',
'outputdata.dat' using 1:40 w l ls 13 notitle 'g_{13}',
'outputdata.dat' using 1:43 w l ls 14 notitle 'g_{14}',
'outputdata.dat' using 1:46 w l ls 15 notitle 'g_{15}',
'outputdata.dat' using 1:49 w l ls 16 notitle 'g_{16}',
'outputdata.dat' using 1:52 w l ls 17 notitle 'g_{17}',
'outputdata.dat' using 1:55 w l ls 18 notitle 'g_{18}',
'outputdata.dat' using 1:58 w l ls 19 notitle 'g_{19}',
'outputdata.dat' using 1:61 w l ls 20 notitle 'g_{20}',
'outputdata.dat' using 1:64 w l ls 21 notitle 'g_{21}',
'outputdata.dat' using 1:67 w l ls 22 notitle 'g_{22}',
'outputdata.dat' using 1:70 w l ls 23 notitle 'g_{23}',
'outputdata.dat' using 1:73 w l ls 24 notitle 'g_{24}',
'outputdata.dat' using 1:76 w l ls 25 notitle 'g_{25}',
'outputdata.dat' using 1:79 w l ls 26 notitle 'g_{26}',
'outputdata.dat' using 1:82 w l ls 27 notitle 'g_{27}'
"





