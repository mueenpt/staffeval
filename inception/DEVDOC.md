# Developer Guide

A short developer-facing doc explaining how the project is organized and how to work on it.

## Project layout (important files)

- `srcs/docker-compose.yml` — defines services, networks and volumes.
- `srcs/requirements/nginx/Dockerfile` — builds the Nginx image and TLS cert.
- `srcs/requirements/nginx/conf/nginx.conf` — Nginx site config, forwards PHP to `wordpress:9000`.
- `srcs/requirements/wordpress/Dockerfile` — builds PHP-FPM + wp-cli and runs `tools/setup.sh`.
- `srcs/requirements/wordpress/tools/setup.sh` — waits for MariaDB, downloads WP, creates `wp-config.php`, installs WP and creates a user.
- `srcs/requirements/mariadb/Dockerfile` — builds MariaDB image and runs `tools/init.sh`.
- `srcs/requirements/mariadb/tools/init.sh` — initializes the database and users when the data directory is empty.

## How images are built and run

- Build and run using Docker Compose from `srcs`:

```bash
cd srcs
docker compose up --build -d
```

- Compose builds images from the `requirements/*` directories and creates two named volumes (`mariadb`, `wordpress`) and a bridge network named `inception`.

## Environment and configuration

- The `srcs/.env` file contains configuration variables used by the `wordpress` and `mariadb` services (DB names and passwords, WP admin credentials, `DOMAIN_NAME`).
- For development, `.env` is convenient; for production move secrets to a secure secrets manager or Docker secrets.

## Extending or debugging

- To change PHP packages or WordPress setup, edit `srcs/requirements/wordpress/Dockerfile` or `tools/setup.sh` and rebuild:

```bash
cd srcs
docker compose build wordpress
docker compose up -d
```

- To inspect logs for a service:

```bash
docker compose logs -f wordpress
```

- To enter a running container for debugging:

```bash
docker compose exec wordpress bash
```

## Notes for contributors

- Keep secrets out of Git. Do not commit `.env` with production credentials.
- Use named volumes for persistence so local host paths are not required.
- If you change database initialization SQL in `mariadb/tools/init.sh`, either remove the database volume or provide a migration strategy so changes take effect.