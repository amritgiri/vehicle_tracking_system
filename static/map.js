// static/js/map.js
document.addEventListener("DOMContentLoaded", function () {
    var map = L.map("map").setView([28.255365, 83.976569], 20);
  
    L.tileLayer("https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png", {
      attribution:
        '&copy; <a href="https://www.openstreetmap.org/copyright">OpenStreetMap</a> contributors',
    }).addTo(map);
  
    function addMarker(latitude, longitude, delay) {
        setTimeout(()=>{

            L.marker([latitude, longitude], {
                icon: L.divIcon({ className: "dot" }),
            })
            .addTo(map)
            .bindPopup("Vehicle Location: " + latitude + "," + longitude)
            .openPopup();
            const end = new Date().getTime(); // Record end time
            console.log("Marker added. Delay:", end - start, "ms");
        }, delay);
    }
  
    function fetchLocations() {
      fetch("/get_locations/")
        .then((response) => response.json())
        .then((data) => {
          data.forEach((location, index) => {
            const delay = (index + 1) * 2000;
            addMarker(location.latitude, location.longitude, delay);
          });
  
          if (data.length > 0) {
            var lastLocation = data[data.length - 1];
            map.setView([lastLocation.latitude, lastLocation.longitude]);
          }
        })
        .catch((error) => console.error("Error:", error));
    }
  
    fetchLocations();
  
    document.getElementById("clear-button").addEventListener("click", function () {
      map.eachLayer(function (layer) {
        if (layer instanceof L.Marker) {
          map.removeLayer(layer);
        }
      });
    });
  });
  