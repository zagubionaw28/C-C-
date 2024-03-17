set terminal png
set output 'wykres.png'
set xlabel 'Wartosc n'
set ylabel 'Przyblizenie liczby Pi'
set title 'Wykres punktowy'
set xrange [500:100000]
set label '' at 1,3.14 point pt 7 lc rgb 'blue'
plot 'dane.txt' using 2:1 with points pt 7 lc rgb 'red', '+' using (0):(3.14) with points pt 7 lc rgb 'blue' title 'Wartosc Pi'
set arrow from 3.14,0 to 3.14,100 nohead lc rgb 'blue'
