document.addEventListener("DOMContentLoaded", function () {
var map = L.map("map").setView([28.256038, 83.977092], 16); // Initial center point

L.tileLayer("https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png", {
    attribution:
        '&copy; <a href="https://www.openstreetmap.org/copyright">OpenStreetMap</a> contributors',
}).addTo(map);

// Function to add a marker to a specific coordinate
function addMarker(latitude, longitude) {
    L.marker([latitude, longitude], {
        icon: L.divIcon({ className: "dot" }),
    })
    .addTo(map)
    .bindPopup("Vehicle Location: " + latitude + "," + longitude)
    .openPopup();
}

// Function to fetch and display locations
function fetchLocations() {
    fetch("/receive_location/")
    .then((response) => response.json())
    .then((data) => {
        // Assuming you want to focus on the first point coordinate
        if (data.length > 0) {
            var firstLocation = data[0];
            map.setView([firstLocation.latitude, firstLocation.longitude]); // Center the map on the first coordinate
        }

        data.forEach((location) => {
            addMarker(location.latitude, location.longitude);
        });
    })
    .catch((error) => console.error("Error:", error));
}

fetchLocations();

// Clear button event listener
document.getElementById("clear-button").addEventListener("click", function () {
    map.eachLayer(function (layer) {
        if (layer instanceof L.Marker) {
            map.removeLayer(layer);
        }
    });
    fetchLocations();
});
});
