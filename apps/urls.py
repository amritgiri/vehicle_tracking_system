# urls.py
from django.urls import path

from .views import *

urlpatterns = [
    path("receive_location/", receive_location, name="receive_location"),
    path("map/", map_view, name="map"),
    path("get_locations/", get_locations, name="get_locations"),
]
