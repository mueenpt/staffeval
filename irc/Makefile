NAME = ircserv

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -Iinclude -Iinclude/command -Iinclude/network
OBJDIR = obj

SRC = src/main.cpp \
      src/network/Server.cpp \
	src/network/Client.cpp \
	src/network/Channel.cpp \
	src/command/Parser.cpp \
	src/command/Pass.cpp \
	src/command/Nick.cpp \
	src/command/User.cpp \
	src/command/Join.cpp \
	src/command/Privmsg.cpp \
	src/command/Kick.cpp \
	src/command/Invite.cpp \
	src/command/Topic.cpp \
	src/command/Mode.cpp \
	src/command/Part.cpp \
	src/command/Quit.cpp

OBJ = $(SRC:src/%.cpp=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

$(OBJDIR)/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re