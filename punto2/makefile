all:estado_0.010000.pdf 
t=0.01

sod_test.x:sod_test.c 
	cc $^ -lm -o $@
estado_0.010000.dat:sod_test.x
	./$^ $t

estado_0.010000.pdf:graficador.py estado_0.010000.dat
	python $^ 
	
