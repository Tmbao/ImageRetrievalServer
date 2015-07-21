sudo psql -h 127.0.0.1 -U postgres -c "DROP DATABASE irserverdb"
sudo psql -h 127.0.0.1 -U postgres -c "CREATE DATABASE irserverdb"

./manage.py syncdb
