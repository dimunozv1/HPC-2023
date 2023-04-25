size := 10 50 100 200 500 1000 2000 3000 4000
threads := 1 2 3 4 5 6 7 8 9 10 11 12
ntests := 5
O0 := 0
O3 := 1

all:  datosO0-eigen-variaNsize datosO3-eigen-variaNsize datosO0-simple-variaNsize datosO3-simple-variaNsize


datosO0-eigen-variaNsize:
	g++ eigen_base.cpp -O0 -o eigen_O0_VariaN.out
	for n in $(size); do \
    	./eigen_O0_VariaN.out $$n $(ntests) $(O0) ; \
    done

datosO3-eigen-variaNsize:
	g++ eigen_base.cpp -O3 -o eigen_O3_VariaN.out
	for n in $(size); do \
    	./eigen_O3_VariaN.out $$n $(ntests) $(O3) ; \
    done

datosO0-simple-variaNsize:
	g++ simple_matmul.cpp -O0 -o simple_O0_VariaN.out
	for n in $(size); do \
    	./simple_O0_VariaN.out $$n $(ntests) $(O0) ; \
    done

datosO3-simple-variaNsize:
	g++ simple_matmul.cpp -O3 -o simple_O3_VariaN.out
	for n in $(size); do \
    	./simple_O3_VariaN.out $$n $(ntests) $(O3) ; \
    done


datosO3-eigen-variaThreads:
	g++ -fopenmp eigen_base_parallel.cpp -O3 -o eigen_O3_parallel.out
	for n in $(threads); do \
    	./eigen_O3_parallel.out $$n $(ntests) $(O3) ; \
    done


clean:
	rm *.txt *.exe *.out *.o