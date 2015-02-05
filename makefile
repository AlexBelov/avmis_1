default:
	icc -std=c99 -O2 -opt-report=2 -qopt-report-phase=vec -D NOALIAS main.c -o icc_vec
	icc -std=c99 -O1 main.c -o icc_unvec
	icc -std=c99 -O1 -D SSE2 main.c -o icc_sse2
	gcc -std=c99 -msse2 -O1 main.c -o gcc

clean:
	rm gcc icc_unvec icc_vec icc_sse2 main.optrpt
