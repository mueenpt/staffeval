# User Guide

This is a simple guide for end users to run and access the WordPress site included in this project.

## Quick start

1. Install Docker and Docker Compose on your machine.
2. Copy the environment file and (optionally) edit values:

```bash
cp srcs/.env .env
```

3. Start the stack from the `srcs` folder:

```bash
cd srcs
docker compose up --build -d
```

4. Open your browser and visit the site at:

- https://<DOMAIN_NAME> (the `DOMAIN_NAME` value is in the `.env` file)

By default in this repository the `.env` values are:

- `DOMAIN_NAME=mdheen.42.fr`
- `MYSQL_DATABASE=wordpress`
- `MYSQL_USER=wpuser`
- `MYSQL_PASSWORD=12345`
- `MYSQL_ROOT_PASSWORD=98765`
- `WP_ADMIN_USER=master`
- `WP_ADMIN_PASSWORD=master123`

These are sample values intended for development only — change them before deploying publicly.

## What this provides

- A WordPress site reachable over HTTPS via the bundled Nginx container.
- Persistent storage for the WordPress files and MariaDB database using Docker volumes.

## Stopping and cleaning up

To stop the stack and remove containers and volumes (data will be removed):

```bash
docker compose down -v
```

## Troubleshooting

- If WordPress shows a database error, ensure the `mariadb` container is healthy and the `.env` credentials match.
- Check container logs with:

```bash
docker compose logs -f
```

- To re-run WordPress setup (if you changed `.env`), remove the `wordpress` volume and restart:

```bash
docker volume rm srcs_wordpress
# then restart
docker compose up --build -d
```

