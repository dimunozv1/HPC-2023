threads := 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
seq_policy := 0
par_policy := 1
par_unseq_policy := 2
Narray := 200000000
ntests := 5

all: datos_seq.txt datos_par.txt datos_par_unseq.txt

datos_seq.txt: parallel_metrics.o
	for n in $(threads); do \
		./parallel_metrics.o $(Narray) $$n $(seq_policy) $(ntests) >> datos_seq.txt; \
	done

datos_par.txt: parallel_metrics.o
	for n in $(threads); do \
		./parallel_metrics.o $(Narray) $$n $(par_policy) $(ntests) >> datos_par.txt; \
	done

datos_par_unseq.txt: parallel_metrics.o
	for n in $(threads); do \
		./parallel_metrics.o $(Narray) $$n $(par_unseq_policy) $(ntests) >> datos_par_unseq.txt; \
	done

parallel_metrics.o: parallel_metrics_algs.cpp
	g++ -std=c++17 parallel_metrics_algs.cpp -ltbb -o parallel_metrics.o

clean:
	rm -rf *.txt *.o
