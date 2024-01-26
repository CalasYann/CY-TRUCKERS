#!/bin/bash

nb_arg=$#
all_arg=$*
arg1=$1

for var in $all_arg ; do
	if [ $var = -h ] ; then
		echo "Un de vos argument vaut -h, voici le manuel d'aide de la fonction"
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

echo "test1"

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
		echo "L'executable viens d'être créé"
		exec=`gcc -o progc/test progc/test.c`
			if [ ! -e progc/test ] ; then 
				echo "La création de l'executable a échoué"
				exit
			fi
		fi
	done
fi

if [ $exec == "0" ] ; then 
	echo "le fichier c est absent ou est au mauvaise endroit"
	exit 1
fi
echo "test2"

ttemp=0 
for var in $doss/* ; do 
	if [ `echo $var | sed 's/.*\///g' ` == temp ] ; then 
		`rm -r -f temp/*`
		ttemp=1
	fi
done

if [ $ttemp == "0" ] ; then 
	`mkdir temp`
	echo "test3"
fi

if [ ! -e images/ ] ; then 
	`mkdir images`
fi

echo "test4"

count=1

for var in $all_arg ; do

	if [ $var == "-d1" ] ; then 
		echo ""
		#faire le traitement D1
	elif [ $var == "-d2" ] ; then
		echo ""
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
		
		time awk -F";" ' NR>1  { ROUTE[$1]+=$5 } END { for (M in ROUTE) printf "%d;%.3f \n",M,ROUTE[M] }' "$arg1" | sort -k2 -t";" -n -r | head | sort -k1 -t";" -n -r > temp/tempL.dat

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
		plot 'temp/tempL.dat' using 2:xtic(1) title'Distance' lc rgb "red"
EOF


	elif [ $var == "-t" ] ; then 
		echo ""	
		#faire le traitement T
	elif [ $var == "-s" ] ; then
		echo " " 
		#faire le traitemet S
	elif [ $count == "1" ] ; then
		echo " "
	else 
		echo "Votre argument numero $count ne correspond pas : $var"	
	fi 
	count=$((count+1))		
	
done


#faire des fonctions pour les différents parcours utiliser time au moment de l'appel de ces fonctions pour avoir le temps d'un traitement


