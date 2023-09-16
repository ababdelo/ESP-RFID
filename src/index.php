<!DOCTYPE html>
<html>
<head>
    <meta http-equiv="refresh" content="5" >
    <link rel="stylesheet" type="text/css" href="../style/style.css" media="screen"/>

	<title> Sensor Data </title>

</head>

<body>

    <h1>SENSOR DATA</h1>
<?php
$sname = "localhost";
$uname = "ababdelo";
$password = "Thewayofthemakersis 1337";
$db_name = "databasecode";

// Create connection
$conn = new mysqli($sname, $uname, $password, $db_name);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

$sql = "SELECT id, sensor, location, value, reading_time FROM sensordata ORDER BY id ASC"; /*select items to display from the sensordata table in the data base*/

echo '<table cellspacing="5" cellpadding="5">
      <tr> 
        <th>ID</th> 
        <th>Date && Time</th> 
        <th>Sensor</thh> 
        <th>Location</th> 
        <th>Value</th>     
      </tr>';
 
if ($result = $conn->query($sql)) {
    while ($row = $result->fetch_assoc()) {
        $row_id = $row["id"];
        $row_reading_time = $row["reading_time"];
        $row_sensor = $row["sensor"];
        $row_location = $row["location"];
        $row_value = $row["value"];
        
        echo '<tr> 
                <td>' . $row_id . '</td> 
                <td>' . $row_reading_time . '</td> 
                <td>' . $row_sensor . '</td> 
                <td>' . $row_location . '</td> 
                <td>' . $row_value . '</td> 
                
              </tr>';
    }
    $result->free();
}

$conn->close();
?> 
</table>

</body>
</html>