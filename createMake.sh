
 # Team T
 # 
 # Student Name: Vojtech Loskot
 # Matric Number: 2424633
 # 
 # Student Name: Kamil Krauze
 # Matric Number: 2414951
 # 
 # Student Name: Harry Inglis
 # Matric Number: 2411653
 #

#!/bin/bash

read -p "gcc or g++ ? " type

case $type in
    "gcc")
        coutput=($(find ./ -type f -name "*.c"))
    ;;
    "g++")
        cppoutput=($(find ./ -type f -name "*.cpp"))
    ;;
    * )
        echo -e "Compiler does not exist or is not supported... exiting"
        exit 1
    ;;
esac

if [ -f ./makefile ]; then
    rm -f -r makefile
else
    touch makefile
    sudo chmod 777 makefile
fi

case $type in
    "gcc")
        srcfiles=$(echo -e ${coutput[@]})
        echo -e $srcfiles
        
        printf "main: $srcfiles" >> makefile
        printf "\n\tgcc -g -Wall -Wextra -Werror -o main $srcfiles" >> makefile
        
        printf "\nclean:" >> makefile
        printf "\n\trm -f -r main" >> makefile
    ;;
    "g++")
        
        srcfiles=$(echo -e ${cppoutput[@]})
        echo -e $srcfiles
        
        printf "main: $srcfiles" >> makefile
        printf "\n\tg++ -g -Wall -Wextra -Werror -o main $srcfiles" >> makefile
        
        printf "\nclean:" >> makefile
        printf "\n\trm -f -r main" >> makefile
    ;;
esac


