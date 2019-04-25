include Makefile.rule

Comiler = gcc

CLIENT = $(wildcard sim_client/*.cpp)
HPS = $(wildcard sim_hps/*.cpp)
LPS = $(wildcard sim_lps/*.cpp)

COMMON_INC_DIR   = $(MYSQLCLIENT_DIR)/include/mysql $(CURL_DIR)/include $(CFITSIO)/include
COMMON_LIB_DIR   = -L$(MYSQLCLIENT_DIR)/lib -L$(OPENSSL_DIR)/lib/ -L$(CURL_DIR)/lib -L$(CFITSIO)/lib
COMMON_FLAGS     = -O3 -lstdc++ -lmysqlclient -lssl -lcrypto -lcurl -lcfitsio

#.PHONY: all clean

client: $(CLIENT)
	$(Comiler) $(CLIENT) $(addprefix -I,$(COMMON_INC_DIR)) $(COMMON_LIB_DIR) $(COMMON_FLAGS) -o client

hps: $(HPS)
	$(Comiler) $(HPS) $(addprefix -I,$(COMMON_INC_DIR)) $(COMMON_LIB_DIR) $(COMMON_FLAGS) -o hps

lps: $(LPS)
	$(Comiler) $(LPS) $(addprefix -I,$(COMMON_INC_DIR)) $(COMMON_LIB_DIR) $(COMMON_FLAGS) -o lps

clean:
	rm -f client hps lps

