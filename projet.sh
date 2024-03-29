#!/bin/bash

nb_arg=$#
all_arg=$*
arg1=$1

for var in $all_arg ; do
	if [ $var = -h ] ; then
		echo "Un de vos argument vaut -h, voici le manuel d'aide de la commande : 
Cette commande est associé a plusieur option, pour l'utilisé correctement il faut mettre en premier argument votre fichier à traiter comme indiqué dans le ReadMe associé.
Les différentes options :
	-d1 pour récupérer les 10 conducteurs avec le plus de trajet
	-d2 pour récupérer les 10 conducteurs avec la plus grandes distances parcourures
	-l pour récupérer les 10 trajets les plus longs
	-t pour récupérer les 10 villes les plus traverser
	-s pour avoir les 50 trajets avec des longueurs d'étapes qui diffèrent le plus"
	exit 
	fi
done
term=`echo $arg1 | sed 's/.*\.//g' `


if [ $nb_arg -lt 2 ] ; then
	echo "Nombre d'argument trop faible"
	exit
elif [ ! -f $arg1 ] ; then
	echo "Votre premier argument n'est pas un fichier"
	exit
elif [ "$term" != csv ] ; then

	echo "Votre fichier n'est pas un fichier .csv"
	exit
fi

doss=`pwd` #regarder le dossier dans lequel on est

dosc=$doss/progc #prendre le dossier ou se situe les fichier .c

exec=0


for var in $dosc/* ; do #prend le contenu du dossier
	if [ -x $var ] ; then 
	echo "L'executable existe déjà"
	exec=$var;
	fi
done

if [ $exec == "0" ] ; then 
	for var in $dosc/* ; do #prend le contenu du dossier
		if [ `echo $var | sed 's/.*\.//g' ` == c ] ; then 
		
		cd progc/
		exec=`make`
		cd ..
			if [ ! -e progc/exec ] ; then 
				echo "La création de l'executable a échoué"
				exit
			fi
		fi
	done
fi

ttemp=0 
for var in $doss/* ; do 
	if [ `echo $var | sed 's/.*\///g' ` == temp ] ; then 
		`rm -r -f temp/*`
		ttemp=1
	fi
done

if [ $ttemp == "0" ] ; then 
	`mkdir temp`
fi

if [ ! -e images/ ] ; then 
	`mkdir images`
fi

count=1

for var in $all_arg ; do

	if [ $var == "-d1" ] ; then 
		echo "Traitement -d1"
		time awk -F';' 'NR > 1 { !DRIVE[$1";"$6]++ }END {for(a in DRIVE) print a ";" DRIVE[a]}' "$arg1" | awk -F';' '{ game[$2] += 1}END {for (a in game) printf ("%s;%s\n", a, game[a])}' | sort -n -r -t";" -k2 | head -10 > temp/tempd1.dat
		gnuplot <<EOF
		set datafile separator ";"
		set terminal pngcairo enhanced font 'Verdana,8' 
		set size ratio 1
		set style data histograms
		set style histogram rowstacked
		set style fill solid #fait un graph avec des colonne rempli
		set boxwidth 0.8
		set output 'images/temphistogrammed1.png'
		

		set xtic rotate by 90 
		set terminal png size 800,800
		unset ytics
		unset x2tics
		set xtics nomirror offset 0,-11
		set y2tics rotate by 45
		
		set y2label 'NB ROUTES' offset 2,0
		set xlabel 'DRIVER NAMES' offset 0,-11
		set xlabel rotate by 180
		set title ' ' offset 0,20
		set ylabel 'Option -d1' offset -2,0
		plot 'temp/tempd1.dat' using 2:xtic(1) axes x1y2 notitle lc rgb "red"

		set terminal wxt
EOF
		convert -rotate 90 images/temphistogrammed1.png images/histogrammed1.png
		rm images/temphistogrammed1.png
		
	elif [ $var == "-d2" ] ; then
		echo "Traitement -d2"
		time awk -F';' 'NR > 1 { NAME[$6]+=$5 }END { for(M in NAME)printf("%s;%.3f\n",M,NAME[M]) }' "$arg1" | sort -t";" -k2 -r -n | head -10 > temp/tempd2.dat
		gnuplot <<EOF
		set datafile separator ";"
		set terminal pngcairo enhanced font 'Verdana,8' 
		set size ratio 1
		set style data histograms
		set style histogram rowstacked
		set style fill solid #fait un graph avec des colonne rempli
		set boxwidth 0.8
		set output 'images/temphistogrammed2.png'
		

		set xtic rotate by 90 
		set terminal png size 800,800
		unset ytics
		unset x2tics
		set xtics nomirror offset 0,-11
		set y2tics rotate by 45
		
		set y2label 'Distance' offset 2,0
		set xlabel 'Drivers' offset 0,-11
		set xlabel rotate by 180
		set title ' ' offset 0,20
		set ylabel 'Option -d2' offset -2,0
		plot 'temp/tempd2.dat' using 2:xtic(1) axes x1y2 notitle lc rgb "red"

		set terminal wxt
EOF
		convert -rotate 90 images/temphistogrammed2.png images/histogrammed2.png
		rm images/temphistogrammed2.png

	elif [ $var == "-l" ] ; then
		echo "Traitement -l en cours"
		
		time awk -F';' 'NR > 1 { NAME[$1]+=$5 }END { for(M in NAME)printf("%s;%.3f\n",M,NAME[M]) }' "$arg1" | sort -t";" -k2 -r -n | head -10 > temp/templ.dat

		gnuplot <<EOF
		set datafile separator ";"
		set terminal pngcairo enhanced font 'Verdana,8' 
		set output 'images/histogrammeL.png'

		set style data histograms 
		set style histogram rowstacked
		set style fill solid
		set boxwidth 0.8
		set title 'Option -l'
		set ytics nomirror
		set ylabel 'Distance' 
		set xlabel 'Route ID'
		plot 'temp/templ.dat' using 2:xtic(1) title'Distance' lc rgb "red"
EOF


	elif [ $var == "-t" ] ; then 
		echo "Traitement -t"	
		time  tac "$arg1" | cut -d";" -f1,2,3,4,6 | ./progc/exec 2
		gnuplot <<EOF
		set datafile separator ";"
		set terminal pngcairo enhanced font 'Verdana,8' 
		set output 'images/histogrammet.png'

		set style data histograms 
		set style histogram clustered
		set style fill solid
		set boxwidth 1.5
  		set xtics rotate by -45

		set ytics nomirror
		set ylabel 'Nombre d'apparition' 
		set xlabel 'Ville'
		plot 'temp/tempt.dat' using 2:xtic(1) title'Total' lc rgb "red",\
		'temp/tempt.dat' using 3:xtic(1) title'Départ' lc rgb "blue" 
EOF

	elif [ $var == "-s" ] ; then
		echo "Traitement -s" 
		time  tac "$arg1" | cut -d";" -f1,5 | ./progc/exec 1


		gnuplot <<EOF
		set datafile separator ";"
		set terminal pngcairo enhanced font 'Verdana,6' 
		set size ratio 0.8
		
		set style line 2 linecolor rgb "#dd181f" linetype 1 linewidth 2
		
		set output "images/GraphiqueS.png"
		set xtics rotate by -45
		set xtic scale 1
		set title " Option -s"
		set xlabel "Routes ID"
		set ylabel "Distance"
		
		set style fill solid 0.5
		set style line 1lc rgb'#0060ad' lt 1 lw 2 pt 7 ps 1.5
		
		
		
		plot "temp/temps.dat" using 0:2:4 with filledcurve fc rgb "#dd181f" title "Distance Max/Min",\
		"temp/temps.dat" using 0:3:xticlabels(1) with lines linestyle 2 title "Distance moyenne (Km)"
		
	

EOF
	elif [ $count == "1" ] ; then
		echo " "
	else 
		echo "Votre argument numero $count ne correspond pas : $var"	
	fi 
	count=$((count+1))		
	
done


cd progc
a=`make clean`
cd ..

