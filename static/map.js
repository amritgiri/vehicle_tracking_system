document.addEventListener("DOMContentLoaded", function () {
    var map = L.map("map").setView([28.256038, 83.977092], 17); // Initial center point and zoom level

    L.tileLayer("https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png", {
        attribution:
            '&copy; <a href="https://www.openstreetmap.org/copyright">OpenStreetMap</a> contributors',
    }).addTo(map);

    // Function to add a marker to a specific coordinate
    function addMarker(latitude, longitude, delay) {
        setTimeout(() => {
            map.setView([latitude, longitude], 18)
            L.marker([latitude, longitude], {
                icon: L.divIcon({ className: "dot" }),
            })
            .addTo(map)
            .bindPopup("Vehicle Location: " + latitude + "," + longitude)
            .openPopup();
        }, delay);
    }

    // Function to fetch and display locations
    function fetchLocations() {
        fetch("/receive_location/")
        .then((response) => response.json())
        .then((data) => {
            data.forEach((location, index) => {
                const delay = (index + 1) * 1000;
                addMarker(location.latitude, location.longitude, delay);
            });

            if (data.length > 0) {
                var lastLocation = data[data.length - 1];
                map.setView([lastLocation.latitude, lastLocation.longitude], 16); // Setting the zoom level to 18
            }
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
