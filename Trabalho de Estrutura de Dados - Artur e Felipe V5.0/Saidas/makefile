CASOS_DIR = ../Casos de teste

all:
	gcc *.c -o test

prog:
	gcc *.c -o test -g
	touch teste_saida.txt
	./test > teste_saida.txt

valgrind:
	gcc -g *.c
	valgrind --leak-check=full ./a.out

clean:
	rm -f test

run-test: all
	@if [ -z "$(T)" ]; then \
		echo "Erro: informe o número do teste com N=número (ex: make test T=2)"; \
		exit 1; \
	fi; \
	TEST_DIR="$(CASOS_DIR)/test$(T)"; \
	echo "-----------------------------"; \
	echo "Rodando teste: $$TEST_DIR"; \
	cp "$$TEST_DIR/comandos.txt" comandos.txt; \
	cp "$$TEST_DIR/leitores.txt" leitores.txt; \
	cp "$$TEST_DIR/livros.txt" livros.txt; \
	valgrind --leak-check=full ./test; \
	echo "Comparando saida.txt com $$TEST_DIR/saida.txt"; \
	diff saida.txt "$$TEST_DIR/saida.txt" || echo "Diferenças encontradas em $$TEST_DIR!"

run-all-tests: all
	@for dir in "$(CASOS_DIR)"/test* ; do \
		echo "-----------------------------"; \
		echo "Rodando teste: $$dir"; \
		cp "$$dir/comandos.txt" comandos.txt; \
		cp "$$dir/leitores.txt" leitores.txt; \
		cp "$$dir/livros.txt" livros.txt; \
		./test; \
		echo "Comparando saida.txt com $$dir/saida.txt"; \
		diff saida.txt "$$dir/saida.txt" || echo "Diferenças encontradas em $$dir!"; \
	done
