# Development Notes

1. clone the repo : `git clone https://github.com/amritgiri/vehicle_tracking_system.git`
2. Install the dependencies : `pip install -r requirements`
3. make migration: `python3 manage.py makemigration`
4. migrate: `python3 manage.py migrate`
5. Run server: `python3 manage.py runserver`
6. Run rabbitmq-server: `sudo systemctl start rabbitmq-server`
7. Run the following command in terminal: 
    ```bash
    celery -A core worker --loglevel=info
    celery -A core beat --loglevel=info
    ```