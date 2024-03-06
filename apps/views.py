import json
import os
import requests

from django.http import JsonResponse
from django.shortcuts import render
from django.views.decorators.csrf import csrf_exempt
from twilio.twiml.messaging_response import MessagingResponse
from .utils import get_twilio_client
from django.conf import settings

from .models import Location


def receive_location(request):
    with open("received_location.json") as f:
        json_data = json.load(f)

    # Return JSON response with data and set safe=False
    return JsonResponse(json_data, safe=False)


@csrf_exempt
def handle_incoming_sms(request):
    client = get_twilio_client()
    messages = client.messages.list(
        to= settings.TWILIO_PHONE_NUMBER,
        # limit=1 # for latest
    )

    if messages:
        message = messages[0]
        message_body = message.body

        if message_body:
            parts = message_body.split(",")
            latitude = parts[0].split(":")[1].strip()
            longitude = parts[1].split(":")[1].strip()

            location_data = {"latitude": latitude, "longitude": longitude}

            # Write the location data to a JSON file
            json_file_path = "./received_location.json"
            if os.path.exists(json_file_path):
                with open(json_file_path, "r") as json_file:
                    data = json.load(json_file)
            else:
                data = []

            # Append the new location data to the existing data list
            data.append(location_data)

            # Write the updated data back to the JSON file
            with open(json_file_path, "w") as json_file:
                json.dump(data, json_file, indent=4)

            return JsonResponse({"status": "success"})
        else:
            return JsonResponse({"status": "error", "message": "No message body found"})

    else:
        return JsonResponse({"status": "error", "message": "No messages found"})


def map_view(request):
    locations = Location.objects.all()
    return render(request, "map.html", {"locations": locations})
