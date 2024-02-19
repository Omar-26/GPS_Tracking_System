# GPS Tracking System

```C
LCD_Write("CSE 211s | Introduction to Embedded Systems");
LCD_Set_Cursor(1,0);
LCD_Write("GPS Tracking System Project");
```

## Table of Contents

| No.    | Section                                   |
| ------ | ----------------------------------------- |
| 01     | [Description](#description)               |
| 02     | [Features](#features)                     |
| 03     | [Installation](#installation)             |
| 04     | [Usage](#usage)                           |
| 05     | [Requirements](#requirements)             |
| 06     | [Contributing](#contributing)             |
| 07     | [License](#license)                       |
| 08     | [Credits](#credits)                       |
| 09     | [Contact](#contact)                       |
| 10     | [Video Demo](#video-demo)                 |
| 11     | [Baseline Path](#baseline-path)           |

## Description

The GPS Distance Tracking System is a project developed as part of the CSE-211s course at CSE Department, Faculty of Engineering, Ain Shams University. The main objective of this project is to create an embedded system that accurately tracks the distance a user travels between two points using GPS coordinates. The system is implemented Using the Texas Insteruments TM4C123G LaunchPad and provides real-time visual feedback to the user through LEDs.

## Features

The GPS subsystem performs the following tasks:

1. Gets the coordinates of the starting point Using UART Protocol.
2. Gets the coordinates of the endpoint and calculates the total distance Between Them.
3. Provides visual feedback to the user using built-in LEDs based on these criteria:
   - If the distance from the target ~ 0 m    | `Green` LED  Turn on _**(destination is reached)**_.
   - If the distance from the target <= 5 m | `Yellow` LED Turn on _**(about to be reached)**_.
   - If the distance from the target > 10 m | `Red` LED Turn on  _**(far away)**_.

The trajectory of the distance traveled must satisfy the following criteria:

1. The total distance between the start and end points should be greater than **100 meters**.
2. The path from the start point to the endpoint should form a **non-straight line** similar to the provided baseline path.

The system calculates the distance between the starting point and the endpoint and compares it with the distance obtained from Google Maps. The error margin should be less than or equal to **5%**.

## Installation

To use the GPS Distance Tracking System, follow these steps:

1. Clone the repository to your local machine:

   ```bash
   https://github.com/Omar-26/GPS_Tracking_System.git
   ```

2. Connect the TM4C123G LaunchPad to a GPS module and configure it to receive GPS coordinates.

3. Open the project in Code Composer Studio (CMake is also required for building).

## Usage

To use the GPS Distance Tracking System, follow these steps:

1. Power on the GPS Distance Tracking System.

2. Select any starting point on Google Maps and mark it as the starting Point.

3. Walk or travel to the destination point.

4. The system will provide visual feedback through the built-in LEDs as follows:
   - `Green` LED | Target destination is reached.
   - `Yellow` LED | Target destination about to be reached (less than 5 meters away).
   - `Red` LED | Target destination is far away (more than 5 meters).

5. Ensure that the calculated distance is within an error margin of 5% compared to Google Maps.

## Requirements

To successfully run the GPS Distance Tracking System, you will need the following:

- TM4C123G LaunchPad
- GPS Module
- Code Composer Studio (CCS) or CMake for building
- UART configuration for GPS module communication

## Contributing

Contributions to the GPS Distance Tracking System project are welcome. To contribute, follow these steps:

1. Fork the repository.

2. Create a new branch for your feature or bug fix.

3. Make your changes and commit them with a detailed description.

4. Push to the branch and create a pull request on GitHub.

## License

This project is licensed under the GNU AGPLv3 LICENSE.

## Credits

This project was developed by Team Work as part of Introduction to Embedded Systems Course. Special thanks to the faculty staff at the CSE Department for their support and guidance throughout the project.

## Contact

For any inquiries or support, please contact:

<table>
<tr>
  <!-- Omar Ashraf -->
    <td align="center" style="word-wrap: break-word; width: 150.0; height: 150.0">
        <a href=>
            <img src=https://avatars.githubusercontent.com/u/59094800?v=4 width="100;"  style="border-radius:50%;align-items:center;justify-content:center;overflow:hidden;padding-top:10px" alt= Omar Ashraf/>
            <br />
            <sub style="font-size:14px"><b>Omar Ashraf</b></sub>
        </a>
    </td>
  <!-- Ahmed Sallam -->
    <td align="center" style="word-wrap: break-word; width: 150.0; height: 150.0">
        <a href=>
            <img src=https://avatars.githubusercontent.com/u/59094800?v=4 width="100;"  style="border-radius:50%;align-items:center;justify-content:center;overflow:hidden;padding-top:10px" alt= Ahmed Sallam/>
            <br />
            <sub style="font-size:14px"><b>Ahmed Sallam</b></sub>
        </a>
    </td>
  <!-- Abdelrahman Ezz -->
    <td align="center" style="word-wrap: break-word; width: 150.0; height: 150.0">
        <a href=>
            <img src=https://avatars.githubusercontent.com/u/59094800?v=4 width="100;"  style="border-radius:50%;align-items:center;justify-content:center;overflow:hidden;padding-top:10px" alt= Abdelrahman Ezz/>
            <br />
            <sub style="font-size:14px"><b>Abdelrahman Ezz</b></sub>
        </a>
    </td>
  <!-- Abdulrahman Ahmed -->
    <td align="center" style="word-wrap: break-word; width: 150.0; height: 150.0">
        <a href=>
            <img src=https://avatars.githubusercontent.com/u/59094800?v=4 width="100;"  style="border-radius:50%;align-items:center;justify-content:center;overflow:hidden;padding-top:10px" alt= Abdulrahman Aaeed/>
            <br />
            <sub style="font-size:14px"><b>Abdulrahman Ahmed</b></sub>
        </a>
    </td>
  <!-- Ahmed Helmy -->
    <td align="center" style="word-wrap: break-word; width: 150.0; height: 150.0">
        <a href=>
            <img src=https://avatars.githubusercontent.com/u/59094800?v=4 width="100;"  style="border-radius:50%;align-items:center;justify-content:center;overflow:hidden;padding-top:10px" alt= Ahmed Helmy/>
            <br />
            <sub style="font-size:14px"><b>Ahmed Helmy</b></sub>
        </a>
    </td>
</tr>
<tr>
  <!-- Mohamed Atta -->
    <td align="center" style="word-wrap: break-word; width: 150.0; height: 150.0">
        <a href=>
            <img src=https://avatars.githubusercontent.com/u/59094800?v=4 width="100;"  style="border-radius:50%;align-items:center;justify-content:center;overflow:hidden;padding-top:10px" alt= Mohamed Atta/>
            <br />
            <sub style="font-size:14px"><b>Mohamed Atta</b></sub>
        </a>
    </td>
  <!-- Kareem Mostafa -->
    <td align="center" style="word-wrap: break-word; width: 150.0; height: 150.0">
        <a href=>
            <img src=https://avatars.githubusercontent.com/u/59094800?v=4 width="100;"  style="border-radius:50%;align-items:center;justify-content:center;overflow:hidden;padding-top:10px" alt= Kareem Mostafa/>
            <br />
            <sub style="font-size:14px"><b>Kareem Mostafa</b></sub>
        </a>
    </td>
  <!-- Khalid Doma -->
    <td align="center" style="word-wrap: break-word; width: 150.0; height: 150.0">
        <a href=>
            <img src=https://avatars.githubusercontent.com/u/59094800?v=4 width="100;"  style="border-radius:50%;align-items:center;justify-content:center;overflow:hidden;padding-top:10px" alt= Khalid Doma/>
            <br />
            <sub style="font-size:14px"><b>Khalid Doma</b></sub>
        </a>
    </td>
  <!-- Blank Space -->
    <td align="center" style="word-wrap: break-word; width: 150.0; height: 150.0">
        <a href=>
            <img src=https://avatars.githubusercontent.com/u/59094800?v=4 width="100;"  style="border-radius:50%;align-items:center;justify-content:center;overflow:hidden;padding-top:10px" alt= Blank Space/>
            <br />
            <sub style="font-size:14px"><b>Blank Space</b></sub>
        </a>
    </td>
  <!-- Blank Space -->
    <td align="center" style="word-wrap: break-word; width: 150.0; height: 150.0">
        <a href=>
            <img src=https://avatars.githubusercontent.com/u/59094800?v=4 width="100;"  style="border-radius:50%;align-items:center;justify-content:center;overflow:hidden;padding-top:10px" alt= Blank Space/>
            <br />
            <sub style="font-size:14px"><b>Blank Space</b></sub>
        </a>
    </td>

</tr>
</table>

## Video Demo

You can find a video demonstration of the GPS Distance Tracking System at the following link: [Link to Video Demo]()

<!-- 
## Baseline Path

The baseline path that should be followed for the GPS Distance Tracking System is shown below:

![Image 1](https://www.mdpi.com/ijgi/ijgi-11-00186/article_deploy/html/images/ijgi-11-00186-g001.png) -->
