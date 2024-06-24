CC        = g++
OBJ       = build
SRCS     += $(wildcard src/*.cpp)
DEPDIR   := $(OBJ)/deps
DEPFILES := $(patsubst src/%.cpp,$(DEPDIR)/%.d,$(SRCS))
OBJS      = $(patsubst src/%.cpp,$(OBJ)/%.o,$(SRCS))
DEPFLAGS  = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d
EXE       = suite
CFLAGS    = -I -g -w -std=c++20 -Wall -Wpedantic `sdl2-config --libs --cflags` 
LDLIBS    = -lm -lstdc++ -lSDL2 

all: $(EXE) 

debug: CFLAGS += -DDEBUG
debug: all

$(DEPFILES):
	@mkdir -p "$(@D)"

$(EXE): $(OBJS) | $(BIN)
	@echo "($(MODE)) Building final executable $@"
	@$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

$(OBJ)/%.o : src/%.cpp $(DEPDIR)/%.d | $(DEPDIR)
	@echo "($(MODE)) Compiling $@"
	@mkdir -p "$(@D)"
	@$(CC) $(DEPFLAGS) $(CFLAGS) -c $< -o $@ 

$(OBJ):
	@mkdir -p $@

$(DEPDIR): 
	@mkdir -p $@

clean:
	rm -rf build $(EXE)

include $(wildcard $(DEPFILES))
