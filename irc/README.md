*This project has been created as part of the 42 curriculum by haiqbal and mdheen.*

# ircserv

## Description

ircserv is a simple IRC server written in C++98 as part of the 42 ft_irc project. It accepts multiple TCP clients simultaneously using non-blocking sockets and a single `poll()` event loop. This allows the server to efficiently monitor the listening socket and all connected client sockets without using threads or processes.

The server handles client authentication and implements the core IRC workflow required to connect through a reference IRC client, join channels, and exchange messages.

Implemented features include:
- PASS, NICK, and USER registration
- JOIN and PART for channel access
- PRIVMSG for direct messages and channel messages
- Channel operators and operator privileges
- KICK, INVITE, TOPIC, and MODE
- Channel modes `i`, `t`, `k`, `o`, and `l`
- Partial message buffering for split IRC commands

## Instructions

### Compilation

Build the project with:

```bash
make
```

Available Makefile targets:
- `make`
- `make clean`
- `make fclean`
- `make re`

### Execution

Run the server with:

```bash
./ircserv <port> <password>
```

Example:

```bash
./ircserv 6667 pass
```

The project was tested on Linux and with `irssi` as the reference client.

## Resources

- RFC 1459 - Internet Relay Chat Protocol: https://www.rfc-editor.org/rfc/rfc1459
- RFC 2812 - Internet Relay Chat: Client Protocol: https://www.rfc-editor.org/rfc/rfc2812
- `man 2 socket`
- `man 2 poll`
- `man 2 bind`
- `man 2 listen`
- `man 2 accept`
- irssi documentation: https://irssi.org/documentation/

### AI usage

AI was used for:
- explaining server behavior and IRC command flow during debugging
- helping identify edge cases in invite/join and channel membership handling
- drafting and structuring this README
- summarizing testing notes and feature coverage

AI was not used to generate the core project design from scratch; the implementation and final decisions were made in the codebase itself.
