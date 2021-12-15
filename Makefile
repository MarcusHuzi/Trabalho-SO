# ------------------- # --- VARIÁVEIS DE AMBIENTE --- # -------------------- #

CPP = g++
RM = rm -f
CFLAGS = -Wall -Wextra
BIN = so_game
ZIP = so_game.zip
OBJ = obj/main.o obj/order.o obj/controller.o obj/meal.o obj/menu.o
LIB = lib/order.hpp lib/controller.hpp lib/meal.hpp lib/menu.hpp

# ------------------- # --- DIRETIVAS PRINCIPAIS --- # -------------------- #

# Global
all: $(BIN)

# Produção do executável
$(BIN): $(OBJ)
	$(CPP) -pthread -lpthread -lrt -I lib/ $(OBJ) -o $(BIN)

# Execução convencional do programa
run:
	./$(BIN)

# Execução do programa com Valgrind
valgrind:
	valgrind -s --tool=memcheck --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(BIN)

# Compressão dos arquivos
zip: clean
	zip -r $(ZIP) Makefile lib/* src/* obj/

# Limpeza de objetos e de executável
clean:
	$(RM) $(BIN) $(ZIP) obj/*.o

# ----------------------- # --- OBJETIFICAÇÃO --- # ------------------------ #

obj/main.o: src/main.cpp $(LIB)
	$(CPP) -c src/main.cpp -o obj/main.o $(CFLAGS)	

obj/order.o: src/order.cpp lib/order.hpp
	$(CPP) -c src/order.cpp -o obj/order.o $(CFLAGS)

obj/controller.o: src/controller.cpp lib/order.hpp lib/controller.hpp
	$(CPP) -c src/controller.cpp -o obj/controller.o $(CFLAGS)

obj/meal.o: src/meal.cpp lib/meal.hpp
	$(CPP) -c src/meal.cpp -o obj/meal.o $(CFLAGS)

obj/menu.o: src/menu.cpp lib/menu.hpp
	$(CPP) -c src/menu.cpp -o obj/menu.o $(CFLAGS)
