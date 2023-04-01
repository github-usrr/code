#!/usr/bin/env bash

unset DB_HOST DB_PORT

echo "Before export:"
envsubst < db_settings.ini
echo

echo "After export:"
export DB_HOST=localhost DB_PORT=55000
envsubst < db_settings.ini
