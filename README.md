# SMS based Vehicle Tracking System using Arduino, GPS and GSM

The Objective of this project is to route, track and know location of vehicles in a large area environment based on the GPS(Global Positioning System) and GSM(Global System for Mobile Communication).

"Vehicle Tracking System" by using GPS and GSM is a simple and cost-effective method for tracking the location of the vehicle. The system used in vehicle will also assist the people while using public transportation as they provide their location. This will also help in maintaining the traffic in the city area. We can provide a unique number for each device installed vehicle and can be track down easily. And the admin of this system can be vehicle owners, Police.

The data received from GPS module is transferred to Arduino which provides the message format that is to be sent to given number. After message is received in endpoint we fetch that data and plot a marker in map. Continuous data is plotted which provides a line or pathway of the vehicle. For the endpoint number we can provide a virtual number which makes it easy to fetch the data.

We would like to express our heartfelt gratitude to all those who have supported us in the completion of this project.

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
