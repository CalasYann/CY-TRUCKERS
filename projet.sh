#!/bin/bash

nb_arg=$#
all_arg=$*
arg1=$1

for var in $all_arg ; do
	if [ $var = -h ] ; then
		echo "Un de vos argument vaut -h, voici le manuel d'aide de la focntion"
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
		time awk -F';' 'NR > 1 { NAME[$6]+=$5 }END { for(M in NAME)printf("%s;%.3f\n",M,NAME[M]) }' datatruck.csv | sort -t";" -k2 -r -n | head -10 > donnees.dat
		gnuplot <<EOF
		set datafile separator ";"
		set terminal pngcairo enhanced font 'Verdana,12' 
		set output 'histogramme.png'

		set style data histograms 
		set style histogram rowstacked
		set style fill solid
		set boxwidth 0.8
		set ytics nomirror
		set xtics rotate by -45
		set ylabel 'Distances' 
		set xlabel 'Drivers'
		plot 'donnees.dat' using 2:xtic(1) title'Distance' lc rgb "blue"
EOF
#il faut transformer le graphique pour le mettre a l'horizontal

	elif [ $var == "-l" ] ; then
		echo "Traitement -l en cours"
		
		time awk -F";" ' NR>1  { ROUTE[$1]+=$5 } END { for (M in ROUTE) printf "%d;%.3f \n",M,ROUTE[M] }' "$arg1" | sort -k2 -t";" -n -r | head | sort -k1 -t";" -n -r > tempL.dat

		gnuplot <<EOF
		set datafile separator ";"
		set terminal pngcairo enhanced font 'Verdana,8' 
		set output 'images/histogrammeL.png'

		set style data histograms 
		set style histogram rowstacked
		set style fill solid
		set boxwidth 0.8

		set ytics nomirror
		set ylabel 'Distance' 
		set xlabel 'Route ID'
		plot 'tempL.dat' using 2:xtic(1) title'Distance' lc rgb "red"
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


