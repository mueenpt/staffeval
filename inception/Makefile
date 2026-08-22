COMPOSE_FILE = srcs/docker-compose.yml

all: up

up:
	docker compose -f $(COMPOSE_FILE) up -d --build

down:
	docker compose -f $(COMPOSE_FILE) down

stop:
	docker compose -f $(COMPOSE_FILE) stop

start:
	docker compose -f $(COMPOSE_FILE) start

clean:
	docker compose -f $(COMPOSE_FILE) down --rmi all

fclean: clean
	docker volume rm -f srcs_mariadb srcs_wordpress

re: fclean all

logs:
	docker compose -f $(COMPOSE_FILE) logs -f

ps:
	docker compose -f $(COMPOSE_FILE) ps

.PHONY: all up down stop start clean fclean re logs ps