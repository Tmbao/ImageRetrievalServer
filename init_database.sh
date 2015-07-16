sudo psql -h 127.0.0.1 -U postgres -c "DROP DATABASE IRServerDB"
sudo psql -h 127.0.0.1 -U postgres -c "CREATE DATABASE IRServerDB"

./manage.py syncdb
