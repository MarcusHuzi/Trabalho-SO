# ------------------- # --- VARIÁVEIS DE AMBIENTE --- # -------------------- #

CPP = g++
RM = rm -f
CFLAGS = -Wall -Wextra
BIN = so_game
ZIP = so_game.zip
OBJ = obj/main.o obj/order.o obj/order_controller.o obj/level_controller.o obj/order_semaphore.o obj/meal.o obj/menu.o obj/level_generator.o
LIB = lib/order.hpp lib/order_controller.hpp lib/level_controller.hpp lib/order_semaphore.hpp lib/meal.hpp lib/menu.hpp lib/level_generator.hpp

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

obj/order_semaphore.o: src/order_semaphore.cpp lib/order_semaphore.hpp lib/order.hpp
	$(CPP) -c src/order_semaphore.cpp -o obj/order_semaphore.o $(CFLAGS)

obj/order_controller.o: src/order_controller.cpp lib/order_controller.hpp lib/order.hpp lib/order_semaphore.hpp
	$(CPP) -c src/order_controller.cpp -o obj/order_controller.o $(CFLAGS)

obj/level_controller.o: src/level_controller.cpp lib/level_controller.hpp lib/order.hpp lib/order_controller.hpp lib/order_semaphore.hpp
	$(CPP) -c src/level_controller.cpp -o obj/level_controller.o $(CFLAGS)

obj/meal.o: src/meal.cpp lib/meal.hpp
	$(CPP) -c src/meal.cpp -o obj/meal.o $(CFLAGS)

obj/menu.o: src/menu.cpp lib/menu.hpp
	$(CPP) -c src/menu.cpp -o obj/menu.o $(CFLAGS)

obj/level_generator: src/level_generator.cpp lib/level_generator.hpp
	$(CPP) -c src/level_generator.cpp -o obj/level_generator.o $(CFLAGS)