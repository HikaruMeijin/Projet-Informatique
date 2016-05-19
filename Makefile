all : traitement

traitement : main.o tas.o conversion.o listePersonne.o listePlanete.o
	gcc -Wall -Wextra $^ -lm -o $@

main.o : main.c tas.h listePersonne.h listePlanete.h conversion.h
	gcc -Wall -Wextra -c $^

tas.o : tas.c tas.h listePersonne.h
	gcc -Wall -Wextra -c $^

conversion.o : conversion.c conversion.h tas.h listePlanete.h listePersonne.h
	gcc -Wall -Wextra -c $^

listePersonne.o : listePersonne.c listePersonne.h
	gcc -Wall -Wextra -c $^

listePlanete.o : listePlanete.c listePlanete.h
	gcc -Wall -Wextra -c $^
	
