set terminal pdf
set output 'avg_dust_height.pdf'

set xlabel "timestep"
set ylabel "average dust height"

unset key

plot './avg_dust_height.dat' with lines