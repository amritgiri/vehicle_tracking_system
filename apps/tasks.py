# tasks.py

from celery import shared_task
from .views import handle_incoming_sms

@shared_task
def fetch_locations_periodically():
    handle_incoming_sms(None)  # Call the view function with a None request
