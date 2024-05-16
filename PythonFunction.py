import re
import serial
import folium
import os


def read_serial_data(port, baud_rate):
    try:
        # Open serial port
        serial_port = serial.Serial(port, baud_rate)
        print("Serial port opened successfully")

        # Read a line from serial port
        received_string = serial_port.readline().decode('utf-8').strip()

        # Print the received string
        print("Received:", received_string)
        lat, lon = parse_serial_data_to_string(received_string)
        print("Latitudes:", lat)
        print("Longitudes:", lon)
        plot_path_on_map(lat, lon)
    except serial.SerialException as e:
        print("Serial Exception:", e)
    finally:
        if serial_port and serial_port.is_open:
            serial_port.close()

def parse_serial_data_to_string(s):
    # Remove any non-numeric characters except '.' and ','
    modified_string = re.sub(r'[^\d.,-]', '', s)

    # Split the cleaned string into individual float strings
    float_strings = modified_string.split(',')

    # Convert float strings back to floats
    float_values = [float(num) for num in float_strings if num]  # Make sure no empty strings are converted

    # Assuming the arrays should be split evenly, we determine the midpoint
    midpoint = len(float_values) // 2

    # Split the float values into two arrays
    latitudes = float_values[:midpoint]
    longitudes = float_values[midpoint:]

    # Remove zero elements from arrays
    latitudes = [lat for lat in latitudes if lat != 0]
    longitudes = [lon for lon in longitudes if lon != 0]

    return latitudes, longitudes


def send_letter_to_COM6(letter):
    try:
        # Open the serial port
        ser = serial.Serial('COM6', 9600, timeout=1)

        # Ensure the serial port is open
        if ser.is_open:
            print(f"Serial port {ser.name} opened successfully.")

            # Send the letter
            ser.write(letter.encode())
            print(f"Sent letter '{letter}' to {ser.name}")

            # Close the serial port
            ser.close()
            print(f"Serial port {ser.name} closed.")
        else:
            print(f"Failed to establish serial communication {ser.name}")

    except serial.SerialException as e:
        print(f"Error occurred : {e}")

def main():
    send_letter_to_COM6('U')
    read_serial_data('COM6', 9600)

def plot_path_on_map(latitudes, longitudes ):
    # Create a map object
    map = folium.Map(location=[latitudes[0], longitudes[0]], zoom_start=15, tiles='OpenStreetMap')

    # Create a list of locations
    locations = list(zip(latitudes, longitudes))

    # Add markers for start and end locations
    folium.Marker(locations[0], tooltip="Start", icon=folium.Icon(color="blue", icon="map-marker")).add_to(map)
    folium.Marker(locations[-1], tooltip="End", icon=folium.Icon(color="red", icon="map-marker")).add_to(map)
    folium.PolyLine(locations, color="blue", weight=2.5, opacity=1).add_to(map)  # lines connecting the path

    # Save and open the map to an HTML file
    map_file_path = "map_plot.html"
    map.save(map_file_path)
    os.system(map_file_path)


if __name__ == "__main__":
    main()
