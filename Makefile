CLIENT = $(wildcard sim_client/*.cpp)
HPS = $(wildcard sim_hps/*.cpp)
LPS = $(wildcard sim_lps/*.cpp)

COMMON_LIB   = /usr/local/opt/mysql-client/include/mysql common/cfitsio
COMMON_FLAGS = -O3

#.PHONY: all clean

client: $(CLIENT) $(COMMON)
	g++ $(CLIENT) $(addprefix -I,$(COMMON_LIB)) $(COMMON_FLAGS) -o client

hps: $(HPS) $(COMMON)
	g++ $(HPS) $(addprefix -I,$(COMMON_LIB)) $(COMMON_FLAGS) -o hps

lps: $(LPS) $(COMMON)
	g++ $(LPS) $(addprefix -I,$(COMMON_LIB)) $(COMMON_FLAGS) -o lps

clean:
	rm -f client hps lps

