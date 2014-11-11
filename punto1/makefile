all: graph_3D.py grafica_3D_name.pdf

grafica_3D_name.pdf: graph_3D.py string_0.500000.dat
	python graph_3D.py string_0.500000.dat

string_0.500000.dat: string.x
	./string.x 0.5

string.x: string.c
	cc string.c -lm -o string.x
clean:
	rm *.dat *.pdf
