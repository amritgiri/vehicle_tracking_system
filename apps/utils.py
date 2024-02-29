from twilio.rest import Client
from django.conf import settings


def get_twilio_client():
    account_sid = settings.TWILIO_ACCOUNT_SID
    auth_token = settings.TWILIO_AUTH_TOKEN
    return Client(account_sid, auth_token)
