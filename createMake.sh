#!/bin/bash

# Created and Designed by Kamil Andrzej Piotr Krauze
#
# Date created: 19/11/2021
#
# This script is free for use, any credit towards the creator is NOT required, however greatly appreciated
# This script should not be retailed or sold at a price on any e-shop.

function dotOIt()
{
	#Remove the ./ at the start and .cpp or .c extension of the file
	removeDot=`echo "$1" | cut -d'.' -f2` # Line 5-6 & 70-71: Remove certain parts of a string - https:/stackoverflow.com/questions/965053/extract-filename-and-extension-in-bash - 19/11/2021
	dotO=`echo "$removeDot" | cut -d'/' -f2`

	printf "\n$dotO.o:\t$1\n" >> makefile
	printf "\tgcc -g -Wall -Wextra -Werror -c $1" >> makefile

	#Append the .o to the file name use that for appending lines to a file
	arrDotOs=(${arrDotOs[@]} "$dotO.o")
	dotOs=$(echo -e ${arrDotOs[@]})
	sed -i "1s/.*/main: $dotOs/" makefile # Line 14-15: Append to some nth line in a file - https://unix.stackexchange.com/questions/162838/how-to-replace-the-first-line-using-sed - 19/11/2021
	sed -i "2s/.*/\tg++ -g -Wall -Wextra -Werror -o main $dotOs/" makefile
}

#Get the first argument
type=$1

if [ -z "$type" ]; # Check if the first argument is empty, if so get user input
then
	read -p "gcc or g++ ? " type
fi

#Depending on the type of compilter use the appropriate find command.
case $type in
"gcc")
coutput=($(find ./ -type f -name "*.c")) #Find file with a specific extension name and set that to a variable
;;
"g++")
cppoutput=($(find ./ -type f -name "*.cpp"))
;;
* )
echo -e "Compiler does not exist or is not supported... exiting"
exit 1
;;
esac

#Remove and create makefile
if [ -f ./makefile ]; then
	rm -f -r makefile
else
	touch makefile
fi

# Write lines to makefile
case $type in
	"gcc")
		srcfiles=$(echo -e ${coutput[@]})
		echo -e $srcfiles

		printf "main: $srcfiles" >> makefile
		printf "\n\tgcc -g -Wall -Wextra -Werror -o main $srcfiles" >> makefile

		for i in "${coutput[@]}"
		do
			dotOIt "$i"
		done

		for j in "${coutput[@]}"
		do
			removeDot=`echo "$j" | cut -d'.' -f2`
			dotO=`echo "$removeDot" | cut -d'/' -f2`
		done

		dotOs=$(echo -e ${arrDotOs[@]})

		printf "\nclean:" >> makefile
		printf "\n\trm -f -r main $dotOs" >> makefile

		printf "\nrebuild:" >> makefile
		printf "\n\trm -f -r main $dotOs" >> makefile
		printf "\n\tmake" >> makefile
	;;
	"g++")

		srcfiles=$(echo -e ${cppoutput[@]})
		echo -e $srcfiles

		printf "main: $srcfiles" >> makefile
		printf "\n\tg++ -g -Wall -Wextra -Werror -o main $srcfiles" >> makefile

		for i in "${cppoutput[@]}"
		do
			dotOIt "$i"
		done

		for j in "${cppoutput[@]}"
		do
			removeDot=`echo "$j" | cut -d'.' -f2`
			dotO=`echo "$removeDot" | cut -d'/' -f2`
		done

		dotOs=$(echo -e ${arrDotOs[@]})

		printf "\nclean:" >> makefile
		printf "\n\trm -f -r main $dotOs" >> makefile

		printf "\nrebuild:" >> makefile
		printf "\n\trm -f -r main $dotOs" >> makefile
		printf "\n\tmake" >> makefile
	;;
esac


