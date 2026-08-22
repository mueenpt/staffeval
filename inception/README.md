*This project has been created as part of the 42 curriculum by mdheen.*

# Description

This project (Inception) is a Docker-based deployment of a LEMP-like stack to run a WordPress site: Nginx (reverse proxy + TLS), PHP-FPM-powered WordPress, and MariaDB. The goal is to demonstrate container orchestration using Docker Compose, build minimal images for each service, and automate WordPress setup using `wp-cli`.

# Project sources included

- `srcs/docker-compose.yml`: Compose file defining services, volumes and network.
- `srcs/requirements/nginx`: Nginx Dockerfile and TLS-enabled site configuration.
- `srcs/requirements/wordpress`: WordPress Dockerfile and `tools/setup.sh` (WP CLI-driven installation).
- `srcs/requirements/mariadb`: MariaDB Dockerfile, config and `tools/init.sh` (DB initialization).

# Instructions

Prerequisites: Docker and Docker Compose (or Docker Engine with Compose plugin) installed.

From the repository root (`inception/`) run:

```bash
# create an .env (sample names shown) and edit values
cp srcs/.env .env
# then bring up the stack
cd srcs
docker compose up --build -d
```

Access WordPress at https://<DOMAIN_NAME> after the containers start (Nginx exposes 443). To stop and remove containers:

```bash
docker compose down -v
```

# Design choices and Docker usage

This project uses Docker Compose to define three services (nginx, wordpress, mariadb) connected via a user-defined bridge network (`inception`) and with named volumes for persistent data (`mariadb`, `wordpress`). Images are built from small Debian-based Dockerfiles under `srcs/requirements/*` and include minimal service setup scripts to automate initialization (WordPress install, DB creation).

Why Docker here:
- Reproducibility: containers ensure consistent behavior across machines.
- Isolation: each service runs in its own container with minimal host footprint.
- Composition: Compose orchestrates multi-container app lifecycle simply.

# Comparisons

- Virtual Machines vs Docker
  - VMs: full OS per VM, heavier resource usage, strong isolation. Good for running different kernels or full OS stacks.
  - Docker: lightweight process-level isolation using container runtimes and namespaces. Faster startup, smaller images, better density for microservices.
  - Choice here: Docker for lightweight development and fast iteration.

- Secrets vs Environment Variables
  - Environment variables: easy to use and suitable for non-sensitive configuration; however, they may leak in process listings and image history.
  - Secrets (Docker secrets / mounted files / external secret managers): better for sensitive data (DB passwords, API keys) because they avoid being baked into images or envs and can be rotated.
  - Choice here: the project uses an `.env` file for simplicity (as common in 42 projects). For production, migrate secrets to a secrets manager or Docker secrets.

- Docker Network vs Host Network
  - Bridge (default) networks: provide isolation and service name DNS resolution between containers (recommended for Compose setups).
  - Host network: containers share the host network namespace (no port mapping required) but loses isolation and service-level port control.
  - Choice here: bridge network (`inception`) to keep services isolated and reachable by service name.

- Docker Volumes vs Bind Mounts
  - Volumes: managed by Docker, decoupled from host paths, good for persistent app data and portability.
  - Bind mounts: mount specific host directories into containers (useful for development and debugging but less portable).
  - Choice here: named Docker volumes for MariaDB and WordPress persistence to maintain portability and clean lifecycle management.

# Resources

- Docker docs: https://docs.docker.com/
- Docker Compose: https://docs.docker.com/compose/
- WordPress: https://wordpress.org/
- WP-CLI: https://wp-cli.org/
- MariaDB: https://mariadb.org/
- Nginx: https://nginx.org/
- Article on containers vs VMs: https://www.docker.com/resources/what-container

# How AI was used

AI-assisted tasks for this repository:
- Drafting and structuring this `README.md` (summarizing architecture, instructions, and comparisons).
- Analyzing project files (`docker-compose.yml`, Dockerfiles, and setup scripts) to extract service details and recommended run instructions.


# Additional notes

- Important files:
  - `srcs/docker-compose.yml` (compose definition)
  - `srcs/requirements/nginx/Dockerfile` (TLS-enabled Nginx)
  - `srcs/requirements/wordpress/tools/setup.sh` (automated WP install)
  - `srcs/requirements/mariadb/tools/init.sh` (DB initialization)