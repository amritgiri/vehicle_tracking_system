import json
import os

from django.http import JsonResponse
from django.shortcuts import render
from django.views.decorators.csrf import csrf_exempt

from .models import Location


def get_locations(request):
    # Load JSON data from file
    with open("test.json") as f:
        json_data = json.load(f)

    # Return JSON response with data and set safe=False
    return JsonResponse(json_data, safe=False)


@csrf_exempt
def receive_location(request):
    if request.method == "POST":
        latitude = float(request.POST.get("latitude"))
        longitude = float(request.POST.get("longitude"))
        Location.objects.create(latitude=latitude, longitude=longitude)
        return JsonResponse({"status": "success"})
    else:
        return JsonResponse(
            {"status": "error", "message": "Only POST requests are allowed."}
        )


def map_view(request):
    locations = Location.objects.all()
    return render(request, "map.html", {"locations": locations})
