from twilio.rest import Client
import json
import os

# Your Twilio Account SID and Auth Token
account_sid = "account_sid"
auth_token =  "auth_token"

# Initialize Twilio client
client = Client(account_sid, auth_token)

# Get all messages from your Twilio account
messages = client.messages.list(to="+17814887695")

# Print message details
if messages:
    for message in messages:
        message_body = message.body
        print(message_body)
        if message_body:
            # Assuming the message body is in the format "Latitude: <latitude>, Longitude: <longitude>"
            parts = message_body.split(',')
            latitude = parts[0].split(':')[1].strip()
            longitude = parts[1].split(':')[1].strip()
            
            # Create a JSON object with latitude and longitude
            location_data = {
                "latitude": latitude,
                "longitude": longitude
            }

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
            
            print("Location data (JSON):", location_data)
        else:
            print("Message body is empty.")
else:
    print("No messages found with the specified criteria.")
