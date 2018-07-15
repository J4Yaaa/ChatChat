ROOT_PATH=$(shell pwd)
SERVER=$(ROOT_PATH)/server
CLIENT=$(ROOT_PATH)/client
DATA_POOL=$(ROOT_PATH)/data_pool
COMM=$(ROOT_PATH)/comm
WINDOW=$(ROOT_PATH)/window
LIB_PATH=$(ROOT_PATH)/lib

L_PATH=-L$(LIB_PATH)/lib

SERVER_OBJ=$(shell ls $(SERVER) | grep -E '\.cc$$' | sed 's/\.cc/\.o/')
SERVER_OBJ+=$(shell ls $(DATA_POOL) | grep -E '\.cc$$' | sed 's/\.cc/\.o/')
SERVER_OBJ+=$(shell ls $(COMM) | grep -E '\.cc$$' | sed 's/\.cc/\.o/')
SERVER_OBJ+=$(shell ls $(WINDOW) | grep -E '\.cc$$' | sed 's/\.cc/\.o/')

CLIENT_OBJ=$(shell ls $(CLIENT) | grep -E '\.cc$$' | sed 's/\.cc/\.o/g')
CLIENT_OBJ+=$(shell ls $(COMM) | grep -E '\.cc$$' | sed 's/\.cc/\.o/')
CLIENT_OBJ+=$(shell ls $(WINDOW) | grep -E '\.cc$$' | sed 's/\.cc/\.o/')

CC=g++

SERVER_BIN=server_chat
CLIENT_BIN=client_chat

INCLUDE=-I$(DATA_POOL) -I$(COMM) -I$(WINDOW) -I$(LIB_PATH)/include
LDFLAGS=-lpthread -ljson -lncurses

.PHONY:all
all:$(SERVER_BIN) $(CLIENT_BIN)

$(SERVER_BIN):$(SERVER_OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS)
	#@$(CC) -o $@ $^ $(LIB) $(L_PATH)
	@echo "linking [$^] to [$@] ... done"

$(CLIENT_BIN):$(CLIENT_OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS)
	#@$(CC) -o $@ $^ $(LIB) $(L_PATH)
	@echo "linking [$^] to [$@] ... done"

%.o:$(CLIENT)/%.cc
	@$(CC) -c $< $(INCLUDE)
	@echo "comping [$^] to [$@] ... done"

%.o:$(SERVER)/%.cc
	@$(CC) -c $< $(INCLUDE)
	@echo "comping [$^] to [$@] ... done"

%.o:$(DATA_POOL)/%.cc
	@$(CC) -c $<
	@echo "comping [$^] to [$@] ... done"

%.o:$(COMM)/%.cc
	@$(CC) -c $< $(INCLUDE)  
	@echo "comping [$^] to [$@] ... done"

%.o:$(WINDOW)/%.cc
	@$(CC) -c $< $(INCLUDE)  
	@echo "comping [$^] to [$@] ... done"

.PHONY:debug
debug:
	echo $(SERVER_OBJ)
	echo $(CLIENT_OBJ)

.PHONY:clean
clean:
	rm -rf *.o $(SERVER_BIN) $(CLIENT_BIN)
