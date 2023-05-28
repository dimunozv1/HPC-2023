points := 1000 120000000 240000000 360000000 480000000 600000000 720000000 840000000 960000000 1080000000 12000000000
threads := 1 2 3 4 5 6 7 8 
N_points:= 1200000000

all: datos_cores.txt datos_n.txt


datos_cores.txt: a.out
	@for n in $(threads);\
    	do\
        	for i in 1 2 3 4 5;\
        	do\
            	mpirun -np $$n a.out $(N_points) 0 >> datos_cores.txt;\
        	done\
    	done

datos_n.txt: a.out
	@for n in $(points);\
    	do\
        	for i in 1 2 3 4 5;\
       		do\
            	mpirun -np 4 a.out $$n  1>> datos_n.txt;\
        	done\
    	done

a.out: pi.cpp
	mpic++ pi.cpp

clean:
	rm -rf *.txt *.o *.out