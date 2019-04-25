Comiler = gcc

CLIENT = $(wildcard sim_client/*.cpp)
HPS = $(wildcard sim_hps/*.cpp)
LPS = $(wildcard sim_lps/*.cpp)

COMMON_INC_DIR   = /usr/local/opt/mysql-client/include/mysql common/cfitsio/include /usr/local/opt/curl/includ
COMMON_LIB_DIR   = -L/usr/local/opt/mysql-client/lib -L/usr/local/opt/openssl/lib/ -L/usr/local/opt/curl/lib -Lcommon/cfitsio/lib
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

